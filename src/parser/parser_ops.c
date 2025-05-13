/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:23:34 by naharumi          #+#    #+#             */
/*   Updated: 2025/05/13 16:29:33 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*get_redir_node(t_data *minishell, t_token *tokens,
	t_token *op)
{
	t_ast	*node;
	t_token	*right;

	node = new_node(op->id);
	if (!node)
		handle_error(MALLOC);
	right = op->next;
	right->prev = NULL;
	op->next = NULL;
	if (op->prev)
	{
		op->prev->next = NULL;
		op->prev = NULL;
	}
	node->left = build_tree(minishell, tokens);
	node->right = build_tree(minishell, right);
	return (node);
}

t_ast	*parse_redir(t_data *minishell, t_token *tokens, t_token *op)
{
	if (!tokens || !op)
		return (NULL);
	if (tokens == op)
	{
		tokens = tokens->next->next;
		if (tokens)
			tokens->prev = NULL;
		op->next->next = NULL;
	}
	else
	{
		op->prev->next = op->next->next;
		if (op->next->next)
			op->next->next->prev = op->prev;
		op->next->next = NULL;
		op->prev = NULL;
	}
	if (op->id == HEREDOC)
		parse_heredoc(minishell, op);
	return (get_redir_node(minishell, tokens, op));
}

t_ast	*parse_operators(t_data *minishell, t_token *tokens, t_token *op)
{
	t_ast	*node;
	t_token	*right;

	if (!tokens || !op)
		return (NULL);
	node = new_node(op->id);
	if (!node)
		handle_error(MALLOC);
	right = split_token_list(tokens, op);
	node->left = build_tree(minishell, tokens);
	node->right = build_tree(minishell, right);
	return (node);
}

t_ast	*parse_token(t_token *tokens)
{
	t_ast	*node;
	int		count;

	if (!tokens || tokens->id != ARG)
		return (NULL);
	node = new_node(tokens->id);
	if (!node)
		handle_error(MALLOC);
	count = count_args(tokens);
	node->args = allocate_mem(count + 1, sizeof(char *));
	if (!node->args)
		handle_error(MALLOC);
	count = 0;
	while (tokens && tokens->id == ARG)
	{
		node->args[count] = ft_strdup(tokens->value);
		if (!node->args[count])
			handle_error(MALLOC);
		count++;
		tokens = tokens->next;
	}
	node->args[count] = NULL;
	return (node);
}

t_ast	*parse_subshell(t_data *minishell, t_token *tokens)
{
	t_ast	*node;

	tokens = remove_outer_paren(tokens);
	node = new_node(SUBSHELL);
	if (!node)
		handle_error(MALLOC);
	node->left = build_tree(minishell, tokens);
	return (node);
}
