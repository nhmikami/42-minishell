/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:53:56 by naharumi          #+#    #+#             */
/*   Updated: 2025/04/08 17:23:12 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	operators_rule(t_token *token)
{
	if (!token->prev || (token->prev->id != ARG
			&& token->prev->id != PAREN_CLOSE))
		return (0);
	if (!token->next || (token->next->id != ARG
			&& token->next->id != PAREN_OPEN))
		return (0);
	return (1);
}

static int	redir_rule(t_token *token)
{
	if (!token->next || token->next->id != ARG)
		return (0);
	return (1);
}

static int	paren_rule(t_token *token)
{
	if (token->id == PAREN_OPEN)
	{
		if (token->prev && token->prev->id >= PAREN_CLOSE)
			return (0);
		if (!token->next || (token->next->id != ARG
				&& token->next->id != PAREN_OPEN))
			return (0);
	}
	if (token->id == PAREN_CLOSE)
	{
		if (!token->prev || (token->prev->id != ARG
				&& token->prev->id != PAREN_CLOSE))
			return (0);
		if (token->next && token->next->id == ARG)
			return (0);
	}
	return (1);
}

int	check_syntax(t_token *token)
{
	int	flag;

	flag = 1;
	while (token)
	{
		if (token->id == AND || token->id == OR || token->id == PIPE)
			flag = operators_rule(token);
		else if (token->id >= REDIR_IN && token->id <= APPEND)
			flag = redir_rule(token);
		else if (token->id == PAREN_OPEN || token->id == PAREN_CLOSE)
			flag = paren_rule(token);
		if (!flag)
			return (print_error(SYNTAX, 2, NULL, token->value));
		token = token->next;
	}
	return (0);
}
