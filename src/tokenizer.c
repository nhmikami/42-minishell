/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:14:10 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/11 21:30:14 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_open_syntax(char *str)
{
	int		i;
	int		quotes;
	int		brackets;
	char	type;
	
	i = 0;
	quotes = 0;
	brackets = 0;
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
		if (str[i] == '(')
			brackets++;
		if (str[i] == ')')
			brackets--;
		if (str[i])
			i++;
	}
	if ((quotes % 2 != 0) || brackets != 0)
		return (0);
	return (1);
}

int	get_id(char *str)
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

int	token_len(char const *str)
{
	int		len;
	char	quote;

	len = 0;
	quote = 0;
	while (str[len] && ft_isspace(str[len]))
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

static char	*allocate_substr(char const *s, int *len)
{
	char	*str;

	if (*s == '\'' || *s == '\"')
		*len = token_len(s) - 2;
	else
		*len = token_len(s);
	str = malloc(sizeof(char) * (*len + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*get_token(char const *s)
{
	int		i;
	int		len;
	char	*str;
	char	quote;

	len = 0;
	str = allocate_substr(s, &len);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (*s == '\'' || *s == '\"')
		{
			quote = *s++;
			while (*s && *s != quote)
				str[i++] = *s++;
			if (*s == quote)
				s++;
		}
		else
			str[i++] = *s++;
	}
	str[i] = '\0';
	return (str);
}

t_token	*new_token(char *value, int id)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->id = id;
	token->value = ft_strdup(value); // malloc
	if (!token->value)
	{
		return (NULL);
	}
	token->next = NULL;
	return (token);
}

void	append_token(t_token **tokens, t_token *new)
{
	t_token	*tmp;

	if (!tokens || !new)
		return;
	if (!*tokens)
		*tokens = new;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_token	*tokenizer(char *input)
{
	int		id;
	int		len;
	char	*value;
	t_token	*tokens;
	t_token	*new;

	if (!input)
		return (NULL);
	if (!check_open_syntax(input))
		return (NULL); // syntax error
	tokens = NULL;
	while (*input)
	{
		while (*input && ft_isspace(*input))
			input++;
		if (*input)
		{
			id = get_id(input);
			value = get_token(input); // malloc
			if (!value)
				return (NULL);
			new = new_token(value, id); // new list node
			free(value);
			append_token(&tokens, new); // append node
		}
		input += token_len(input);
	}
	return (tokens);
}
