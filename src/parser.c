/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:53:56 by naharumi          #+#    #+#             */
/*   Updated: 2025/04/08 17:23:12 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// utils
t_ast	*new_node(int id)
{
	t_ast	*node;
	
	node = allocate_mem(1, sizeof(t_ast));
	if (!node)
	{
		handle_error(MALLOC);
		return (NULL);
	}
	node->id = id;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

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
	tokens = tokens->next;
	tokens->prev->next = NULL;
	tokens->prev = NULL;
	last->prev->next = NULL;
	last->prev = NULL;
	return (remove_outer_paren(tokens));
}

// check syntax
int	operators_rule(t_token *token)
{
	if (!token->prev || (token->prev->id != ARG && token->prev->id != PAREN_CLOSE))
		return (0);
	if (!token->next || (token->next->id != ARG && token->next->id != PAREN_OPEN))
		return (0);
	return (1);
}

int	redir_rule(t_token *token)
{
	if (!token->next || token->next->id != ARG)
		return (0);
	return (1);
}

int	paren_rule(t_token *token)
{
	if (token->id == PAREN_OPEN)
	{
		if (token->prev && token->prev->id >= PAREN_CLOSE)
			return (0);
		if (!token->next || (token->next->id != ARG && token->next->id != PAREN_OPEN))
			return (0);
	}
	if (token->id == PAREN_CLOSE)
	{
		if (!token->prev || (token->prev->id != ARG && token->prev->id != PAREN_CLOSE))
			return (0);
		if (token->next && token->next->id == ARG)
			return (0);
	}
	return (1);
}

int	check_syntax(t_token *token)
{
	if (token->id == AND || token->id == OR || token->id == PIPE)
		return (operators_rule(token));
	else if (token->id >= REDIR_IN && token->id <= APPEND)
		return (redir_rule(token));
	else if (token->id == PAREN_OPEN || token->id == PAREN_CLOSE)
		return (paren_rule(token));
	return (1);
}

// search
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
		if ((curr->id >= REDIR_IN && curr->id <= APPEND) && paren == 0)
			last = curr;
		curr = curr->next;
	}
	return (last);
}

// build tree
t_ast	*parse_token(t_token *tokens)
{
	t_ast	*node;
	int		count;
	
	if (!tokens || tokens->id != ARG)
		return (NULL);
	node = new_node(tokens->id);
	if (!node) {
		handle_error(MALLOC);
		return (NULL);
	}
	count = count_args(tokens);
	node->args = allocate_mem(count + 1, sizeof(char *));
	if (!node->args) {
		handle_error(MALLOC);
		return (NULL);
	}
	count = 0;
	while (tokens && tokens->id == ARG)
	{ 
		node->args[count] = ft_strdup(tokens->value); // malloc
		if (!node->args[count])
		{
			handle_error(MALLOC);
			return (NULL);
		}
		count++;
		tokens = tokens->next;
	}
	node->args[count] = NULL;
	return (node);
}

t_ast	*parse_heredoc(t_token *tokens, char *delimiter)
{
	t_ast	*node;
	int		count;

	node = new_node(ARG);
	if (!tokens || tokens->id != ARG)
		count = 1;
	else
		count = count_args(tokens);
	node->args = allocate_mem(count + 2, sizeof(char *));
	if (!node->args) {
		handle_error(MALLOC);
		return (NULL);
	}
	count = 0;
	if (!tokens || tokens->id != ARG)
		node->args[count++] = ft_strdup("cat");
	while (tokens && tokens->id == ARG)
	{ 
		node->args[count] = ft_strdup(tokens->value);
		if (!node->args[count])
		{
			handle_error(MALLOC);
			return (NULL);
		}
		count++;
		tokens = tokens->next;
	}
	node->args[count] = exec_heredoc(delimiter);
	node->args[count + 1] = NULL;
	return (node);
}


t_ast	*parse_redir(t_token *tokens, t_token *op)
{
	t_ast	*node;

	if (!tokens || !op)
		return (NULL);
	if (tokens == op) // é o primeiro da lista
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
		return (parse_heredoc(tokens, op->next->value));
	node = new_node(op->id);
	if (!node)
	{
		handle_error(MALLOC);
		return (NULL);
	}
	node->left = build_tree(tokens);
	node->right = build_tree(op->next);
	return (node);
}

t_ast	*parse_operators(t_token *tokens, t_token *op)
{
	t_ast	*node;
	t_token	*right;

	if (!tokens || !op)
		return (NULL);
	node = new_node(op->id);
	if (!node)
	{
		handle_error(MALLOC);
		return (NULL);
	}
	right = split_token_list(tokens, op);
	node->left = build_tree(tokens);
	node->right = build_tree(right);
	return (node);
}

t_ast	*build_tree(t_token *tokens)
{
	t_token	*op;

	tokens = remove_outer_paren(tokens);
	op = search_and_or(tokens);
	if (op)
		return (parse_operators(tokens, op));
	op = search_pipe(tokens);
	if (op)
		return (parse_operators(tokens, op));
	op = search_redir(tokens);
	if (op)
		return (parse_redir(tokens, op));
	return (parse_token(tokens));
}
