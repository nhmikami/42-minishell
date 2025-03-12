/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:14:10 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/12 15:59:54 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	check_close_syntax(char *str, char type)
// {

// }

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
		if (str[i] == '\'' || str[i] == '\"') //carol: verifica aspas dentro de aspas?
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
		{
			brackets--;
			if (brackets < 0) //carol: significa que ) veio antes de (
				handle_error(SINTAX);
		}
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
	while (str[len] && !ft_isspace(str[len]))
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
		*len = token_len(s) - 2; //VERIFICAÇÃO NAO PODE SER FEITA NO TOKEN_LEN?
	else
		*len = token_len(s);
	str = malloc(sizeof(char) * (*len + 1));
	if (!str)
		handle_error(MALLOC);
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
		handle_error(MALLOC);
	token->id = id;
	token->value = ft_strdup(value);
	if (!token->value)
		handle_error(MALLOC);
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
	}
}

void tokenizer(char *input, t_token **tokens)
{
	int		id;
	char	*value;
	t_token	*new;

	if (!check_open_syntax(input))
		handle_error(SINTAX);
	while (*input)
	{
		while (*input && ft_isspace(*input))
			input++;
		if (*input)
		{
			id = get_id(input);
			value = get_token(input); // malloc
			new = new_token(value, id); // new list node
			printf("node: %i, %s\n", new->id, new->value);
			free(value);
			append_token(tokens, new); // append node
		}
		input += token_len(input);
	}
}
