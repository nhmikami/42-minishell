/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:14:10 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/09 18:55:32 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_id(char const *str)
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
		handle_error(MALLOC);
	while (i < len)
		str[i++] = *s++;
	str[i] = '\0';
	return (str);
}

t_token	**tokenizer(char *input)
{
	int		id;
	char	*value;
	t_token	*new;
	t_token	**tokens;

	tokens = allocate_mem(1, sizeof(t_token *));
	if (!tokens)
		handle_error(MALLOC);
	*tokens = NULL;
	while (*input)
	{
		while (*input && ft_isspace(*input))
			input++;
		if (*input)
		{
			id = get_id(input);
			value = get_token(input, id);
			new = new_token(value, id);
			deallocate_mem(value);
			append_token(tokens, new);
			input += token_len(input, id);
		}
	}
	return (tokens);
}
