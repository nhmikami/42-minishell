/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:51:31 by naharumi          #+#    #+#             */
/*   Updated: 2025/05/08 14:51:31 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	operators_rule(t_token *token)
{
	if (!token->prev || !token->next)
		return (print_error(SYNTAX, 2, NULL, token->value));
	if (token->prev->id != ARG && token->prev->id != PAREN_CLOSE)
		return (print_error(SYNTAX, 2, NULL, token->prev->value));
	if (token->next->id != ARG && token->next->id != PAREN_OPEN
		&& !(token->next->id >= REDIR_IN && token->next->id <= APPEND))
		return (print_error(SYNTAX, 2, NULL, token->next->value));
	return (0);
}

static int	redir_rule(t_token *token)
{
	if (!token->next)
		return (print_error(SYNTAX, 2, NULL, token->value));
	if (token->next->id != ARG)
		return (print_error(SYNTAX, 2, NULL, token->next->value));
	return (0);
}

static int	paren_rule(t_token *token)
{
	if (token->id == PAREN_OPEN)
	{
		if (token->prev && token->prev->id >= PAREN_CLOSE)
			return (print_error(SYNTAX, 2, NULL, token->prev->value));
		if (!token->next || (token->next->id != ARG
				&& token->next->id != PAREN_OPEN))
			return (print_error(SYNTAX, 2, NULL, token->next->value));
	}
	if (token->id == PAREN_CLOSE)
	{
		if (!token->prev)
			return (print_error(SYNTAX, 2, NULL, token->value));
		if (token->prev->id != ARG && token->prev->id != PAREN_CLOSE)
			return (print_error(SYNTAX, 2, NULL, token->prev->value));
		if (token->next && token->next->id == ARG)
			return (print_error(SYNTAX, 2, NULL, token->prev->value));
	}
	return (0);
}

int	check_syntax(t_data *minishell, t_token *token)
{
	int	status;

	status = 0;
	while (token)
	{
		if (token->id == AND || token->id == OR || token->id == PIPE)
			status = operators_rule(token);
		else if (token->id >= REDIR_IN && token->id <= APPEND)
			status = redir_rule(token);
		else if (token->id == PAREN_OPEN || token->id == PAREN_CLOSE)
			status = paren_rule(token);
		if (status)
		{
			update_exit_status(minishell, status);
			return (status);
		}
		token = token->next;
	}
	return (status);
}
