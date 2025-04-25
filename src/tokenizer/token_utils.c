/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:14:10 by naharumi          #+#    #+#             */
/*   Updated: 2025/04/09 18:55:32 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value, int id)
{
	t_token	*token;

	token = allocate_mem(1, sizeof(t_token));
	if (!token)
		handle_error(MALLOC);
	token->id = id;
	token->value = ft_strdup(value);
	if (!token->value)
		handle_error(MALLOC);
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

	if (!tokens)
		return ;
	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		if (tmp->value)
			deallocate_mem(tmp->value);
		deallocate_mem(tmp);
	}
}
