/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:14:10 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/02 16:04:30 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// utils
t_token	*new_token(char *value, int id)
{
	t_token	*token;

	token = allocate_mem(1, sizeof(t_token));
	if (!token)
	{
		handle_error(MALLOC);
		return (NULL);
	}
	token->id = id;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		handle_error(MALLOC);
		return (NULL);
	}
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

void	append_token(t_token **tokens, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (*tokens == NULL)
		*tokens = new;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		if (tmp->value)
			deallocate_mem(tmp->value);
		deallocate_mem(tmp);
	}
}

int	check_open_quotes(char *str)
{
	int		i;
	int		quotes;
	char	type;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			type = str[i];
			quotes++;
			i++;
			while (str[i] && str[i] != type)
				i++;
			if (str[i] == type)
				quotes++;
		}
		if (str[i])
			i++;
	}
	if (quotes % 2 != 0)
		return (0);
	return (1);
}

int	check_open_syntax(char *str)
{
	int		i;
	int		paren;

	i = 0;
	paren = 0;
	if (!check_open_quotes(str))
		return (0);
	while (str[i])
	{
		if (str[i] == '(')
			paren++;
		if (str[i] == ')')
		{
			paren--;
			if (paren < 0)
				return (0);
		}
		if (str[i])
			i++;
	}
	if (paren != 0)
		return (0);
	return (1);
}

// tokenizer
int	get_id(char const *str)
{
	if (!ft_strncmp(str, "&&", 2))
		return (AND);
	else if (!ft_strncmp(str, "||", 2))
		return (OR);
	else if (!ft_strncmp(str, "|", 1))
		return (PIPE);
	else if (!ft_strncmp(str, "(", 1))
		return (PAREN_OPEN);
	else if (!ft_strncmp(str, ")", 1))
		return (PAREN_CLOSE);
	else if (!ft_strncmp(str, ">>", 2))
		return (APPEND);
	else if (!ft_strncmp(str, "<<", 2))
		return (HEREDOC);
	else if (!ft_strncmp(str, "<", 1))
		return (REDIR_IN);
	else if (!ft_strncmp(str, ">", 1))
		return (REDIR_OUT);
	else
		return (ARG);
}

int	token_len(char const *str, int id)
{
	int		len;
	char	quote;

	len = 0;
	quote = 0;
	if (id == PIPE || id == PAREN_OPEN || id == PAREN_CLOSE
		|| id == REDIR_IN || id == REDIR_OUT)
		return (1);
	if (id == AND || id == OR || id == APPEND || id == HEREDOC)
		return (2);
	while (str[len] && !ft_isspace(str[len]) && (get_id(&str[len]) == ARG))
	{
		if (str[len] == '\'' || str[len] == '\"')
		{
			quote = str[len];
			len++;
			while (str[len] && str[len] != quote)
				len++;
			if (str[len] == quote)
				len++;
		}
		else
			len++;
	}
	return (len);
}

char	*get_token(char const *s, int id)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = token_len(s, id);
	str = allocate_mem(len + 1, sizeof(char));
	if (!str)
	{
		handle_error(MALLOC);
		return (NULL);
	}
	while (i < len)
		str[i++] = *s++;
	str[i] = '\0';
	return (str);
}

t_token *tokenizer(char *input)
{
	int		id;
	char	*value;
	t_token	*new;
	t_token	*tokens;

	if (!check_open_syntax(input))
	{
		handle_error(SYNTAX);
		return (NULL);
	}
	tokens = NULL;
	while (*input)
	{
		while (*input && ft_isspace(*input))
			input++;
		if (*input)
		{
			id = get_id(input);
			value = get_token(input, id); // malloc
			if (!value)
			{
				handle_error(MALLOC);
				return (NULL);
			}
			new = new_token(value, id); // malloc
			if (!new)
			{
				handle_error(MALLOC);
				return (NULL);
			}
			deallocate_mem(value);
			//printf("node: %i, %s\n", new->id, new->value); // apagar!!!!
			append_token(&tokens, new);
		}
		input += token_len(input, id);
	}
	return (tokens);
}
