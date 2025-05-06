/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:53:56 by naharumi          #+#    #+#             */
/*   Updated: 2025/04/08 17:23:12 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*search_and_or(t_token *tokens)
{
	t_token	*curr;
	t_token	*last;
	int		paren;

	paren = 0;
	curr = tokens;
	last = NULL;
	while (curr)
	{
		if (curr->id == PAREN_OPEN)
			paren++;
		else if (curr->id == PAREN_CLOSE)
			paren--;
		if ((curr->id == AND || curr->id == OR) && paren == 0)
			last = curr;
		curr = curr->next;
	}
	return (last);
}

t_token	*search_pipe(t_token *tokens)
{
	t_token	*curr;
	t_token	*last;
	int		paren;

	paren = 0;
	curr = tokens;
	last = NULL;
	while (curr)
	{
		if (curr->id == PAREN_OPEN)
			paren++;
		else if (curr->id == PAREN_CLOSE)
			paren--;
		if (curr->id == PIPE && paren == 0)
			last = curr;
		curr = curr->next;
	}
	return (last);
}

t_token	*search_redir(t_token *tokens)
{
	t_token	*curr;
	int		paren;

	paren = 0;
	curr = tokens;
	while (curr)
	{
		if (curr->id == PAREN_OPEN)
			paren++;
		else if (curr->id == PAREN_CLOSE)
			paren--;
		if ((curr->id >= REDIR_IN && curr->id <= APPEND) && paren == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
