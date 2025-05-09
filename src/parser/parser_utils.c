/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:53:56 by naharumi          #+#    #+#             */
/*   Updated: 2025/04/08 17:23:12 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_token *tokens)
{
	int		count;
	t_token	*curr;

	count = 0;
	curr = tokens;
	while (curr && curr->id == ARG)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

t_token	*split_token_list(t_token *tokens, t_token *op)
{
	t_token	*right;

	right = NULL;
	if (!tokens || !op)
		return (NULL);
	if (op->next)
	{
		right = op->next;
		right->prev = NULL;
	}
	if (op->prev)
		op->prev->next = NULL;
	op->prev = NULL;
	op->next = NULL;
	return (right);
}

static t_token	*trim_parens(t_token *tokens, t_token *last)
{
	t_token	*new_start;

	new_start = tokens->next;
	new_start->prev = NULL;
	tokens->next = NULL;
	last->prev->next = NULL;
	last->prev = NULL;
	return (new_start);
}

t_token	*remove_outer_paren(t_token *tokens)
{
	t_token	*last;
	t_token	*curr;
	int		paren;

	if (!tokens || tokens->id != PAREN_OPEN)
		return (tokens);
	last = tokens;
	while (last->next)
		last = last->next;
	if (last->id != PAREN_CLOSE)
		return (tokens);
	paren = 0;
	curr = tokens;
	while (curr)
	{
		if (curr->id == PAREN_OPEN)
			paren++;
		else if (curr->id == PAREN_CLOSE)
			paren--;
		if (paren == 0 && curr != last)
			return (tokens);
		curr = curr->next;
	}
	return (remove_outer_paren(trim_parens(tokens, last)));
}
