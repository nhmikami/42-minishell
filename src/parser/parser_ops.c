/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:53:56 by naharumi          #+#    #+#             */
/*   Updated: 2025/04/08 17:23:12 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parse_operators(t_token *tokens, t_token *op, t_data *minishell)
{
	t_ast	*node;
	t_token	*right;

	if (!tokens || !op)
		return (NULL);
	node = new_node(op->id);
	if (!node)
		handle_error(MALLOC);
	right = split_token_list(tokens, op);
	node->left = build_tree(tokens, minishell);
	node->right = build_tree(right, minishell);
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

static t_ast	*parse_heredoc(t_token *tokens, char *delimiter,
		t_data *minishell)
{
	t_ast	*node;
	int		count;

	node = new_node(ARG);
	if (!tokens || tokens->id != ARG)
		count = 1;
	else
		count = count_args(tokens);
	node->args = allocate_mem(count + 2, sizeof(char *));
	if (!node->args)
		handle_error(MALLOC);
	count = 0;
	if (!tokens || tokens->id != ARG)
		node->args[count++] = ft_strdup("cat");
	while (tokens && tokens->id == ARG)
	{
		node->args[count] = ft_strdup(tokens->value);
		if (!node->args[count])
			handle_error(MALLOC);
		count++;
		tokens = tokens->next;
	}
	node->args[count] = exec_heredoc(delimiter, minishell);
	node->args[count + 1] = NULL;
	return (node);
}

static t_ast	*parse_simple_redir(t_token *tokens, t_token *op,
		t_data *minishell)
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
	node->left = build_tree(tokens, minishell);
	node->right = build_tree(right, minishell);
	return (node);
}

t_ast	*parse_redir(t_token *tokens, t_token *op, t_data *minishell)
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
		return (parse_heredoc(tokens, op->next->value, minishell));
	return (parse_simple_redir(tokens, op, minishell));
}
