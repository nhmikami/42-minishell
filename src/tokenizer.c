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
	else if (ft_isspace(*str))
		return (SPACES);
	else
		return (WORD);
}


t_token	**tokenizer(char *input)
{
	int		i;
	int		len;
	char	**arr;
	t_token	**token;
	int		identifier;
	int		id;

	if (!input)
		return (NULL);
	if (!check_open_syntax(input))
		return (NULL); // syntax error
	while (*input)
	{
		id = get_id(input);
		input++;
	}
	i = 0;
	arr = ft_split(input, " ");
	len = ft_arrlen(arr);
	token = maloc((len + 1) * sizeof(token));
	while (arr[i])
	{
		identifier = identify_keyword(arr[i]);
		if (identifier)
		{
			token[i]->value = arr[i];
			token[i]->id = identifier;
		}
		i++;
	}
	return (token);
}