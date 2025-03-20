/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:53:56 by naharumi          #+#    #+#             */
/*   Updated: 2025/03/20 16:30:00 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*new_node(int id)
{
	t_ast	*node;
	
	node = malloc(sizeof(t_ast));
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

int	count_args(t_tokens *tokens)
{
	int			count;
	t_tokens	*curr;

	count = 0;
	curr = tokens;
	while (curr && curr->id == ARG)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

t_ast	*parse_token(t_tokens **tokens)
{
	int		count;
	t_ast	*node;

	if (!*tokens || (*tokens)->id != ARG)
		return (NULL);
	node = new_node(CMD);
	if (!node)
		return (NULL);
	count = count_args(*tokens);
	node->args = malloc(sizeof(char *) * (count + 1));
	if (!node->args){
		handle_error(MALLOC);
		free(node);
		return (NULL);
	}
	count = 0;
	while (*tokens && (*tokens)->id == ARG)
	{ 
		node->args[count] = ft_strdup((*tokens)->value);
		if (!node->args[count])
		{
			handle_error(MALLOC);
			// free em args[i], args, node
			return (NULL);
		}
		count++;
		*tokens = (*tokens)->next;
	}
	node->args[count] = NULL;
	return (node);
}

t_ast	*parse_redir(t_tokens **tokens)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*node;

	left = parse_token(tokens);
	if (*tokens && ((*tokens)->id == REDIR_IN || (*tokens)->id == REDIR_OUT 
		|| (*tokens)->id == APPEND || (*tokens)->id == HEREDOC))
	{
		node = new_node((*tokens)->id);
		*tokens = (*tokens)->next;
		if (!*tokens || (*tokens)->id != ARG)
		{
			handle_error(SYNTAX);
			free(node);
			return (NULL);
		}
		right = parse_token(tokens);
		if (!right)
		{
			handle_error(MALLOC);
			free(node);
			return (NULL);
		}
		node->left = left;
		node->right = right;
		left = node;
	}
	return (left);
}

t_ast	*parse_pipe(t_tokens **tokens)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*node;

	left = parse_redir(tokens);
	if (!left)
		return (NULL);
	while (*tokens && (*tokens)->id == PIPE)
	{
		*tokens = (*tokens)->next;
		right = parse_redir(tokens);
		if (!right)
		{
			handle_error(SYNTAX);
			free_ast(left);
			return (NULL);
		}
		node = new_node(PIPE);
		node->left = left;
		node->right = right;
		left = node;
	}
	return (left);
}

t_ast	*parse_logical_operators(t_tokens **tokens)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*node;
	int		op;

	left = parse_group(tokens);
	if (!left)
		return (NULL);
	while (*tokens && ((*tokens)->id == AND || (*tokens)->id == OR))
	{
		op = (*tokens)->id;
		*tokens = (*tokens)->next;
		right = parse_group(tokens);
		if (!right)
		{
			handle_error(SYNTAX);
			free_ast(left);
			return (NULL);
		}
		node = new_node(op);
		node->left = left;
		node->right = right;
		left = node;
	}
	return (left);
}

t_ast	*parse_group(t_tokens **tokens)
{
	t_ast	*node;

	if (!*tokens || (*tokens)->id != PAREN_OPEN)
		return (parse_pipe(tokens));
	*tokens = (*tokens)->next;
	node = parse_logical_operators(tokens);
	if (!node)
		return (NULL);
	if (!*tokens || (*tokens)->id != PAREN_CLOSE)
	{
		handle_error(SYNTAX);
		free_ast(node);
		return (NULL);
	}
	*tokens = (*tokens)->next;
	return (node);
}

t_ast	*parser(t_token *tokens)
{
	t_ast	*root;

	root = parse_logical_operators(&tokens);
	return (root);
}
