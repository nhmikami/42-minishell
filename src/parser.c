/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:53:56 by naharumi          #+#    #+#             */
/*   Updated: 2025/03/24 20:08:38 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	// if (!token->prev || token->prev->id != ARG) // dúvida??
	// 	return (0);
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

// utils
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

t_token	*cut_token_list(t_token **tokens, t_token *token_to_cut)
{
	t_token	*right;

	if (!tokens || !*tokens || !token_to_cut)
		return (NULL);
	if (token_to_cut->next)
	{
		right = token_to_cut->next;
		right->prev = NULL;
	}
	if (token_to_cut->prev)
		token_to_cut->prev->next = NULL;
	token_to_cut->prev = NULL;
	token_to_cut->next = NULL;
	free(token_to_cut);
	return (right);
}

t_token	**trim_paren(t_token **tokens)
{
	t_token	*first;
	t_token	*last;
	t_token	*aux;

	if (!tokens || !*tokens || (*tokens)->id != PAREN_OPEN)
		return (tokens);
	*tokens = (*tokens)->next;
	first = (*tokens)->prev;
	last = *tokens;
	while (last->next)
		last = last->next;
	if (first->id == PAREN_OPEN && last->id == PAREN_CLOSE)
	{
		first->next = NULL;
		(*tokens)->prev = NULL;
		free(first);
		aux = last->prev;
		aux->next = NULL;
		last->prev = NULL;
		free(last);
	}
	return (tokens);
}

// search
t_token	*search_and_or(t_token **tokens)
{
	t_token	*curr;
	t_token	*last;
	int		paren;

	paren = 0;
	curr = *tokens;
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
	if (!last && (*tokens)->id == PAREN_OPEN)
		return (search_and_or(trim_paren(tokens)));
	return (last);
}

t_token	*search_pipe(t_token **tokens)
{
	t_token	*curr;
	t_token	*last;
	int		paren;

	paren = 0;
	curr = *tokens;
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
	if (!last && (*tokens)->id == PAREN_OPEN)
		return (search_pipe(trim_paren(tokens)));
	return (last);
}

t_token	*search_redir(t_token **tokens)
{
	t_token	*curr;
	int		paren;

	paren = 0;
	curr = *tokens;
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
	if ((*tokens)->id == PAREN_OPEN)
		return (search_redir(trim_paren(tokens)));
	return (NULL);
}

// parser
t_token	*get_left_leg(t_token *token_to_cut)
{
	t_token	*left;

	if (!token_to_cut)
		return (NULL);
	if (token_to_cut->prev)
	{
		left = token_to_cut->prev;
		left->next = NULL;
	}
	while (left->prev)
		left = left->prev;
	return (left);
}

t_token	*get_right_leg(t_token *token_to_cut)
{
	t_token	*right;

	if (!token_to_cut)
		return (NULL);
	if (token_to_cut->next)
	{
		right = token_to_cut->next;
		right->prev = NULL;
	}
	return (right);
}

t_ast	*parse_token(t_token *tokens)
{
	t_ast	*node;
	int		count;
	

	if (!tokens || tokens->id != ARG)
		return (NULL);
	node = new_node(CMD);
	if (!node)
		return (NULL);
	count = count_args(tokens);
	node->args = malloc(sizeof(char *) * (count + 1));
	if (!node->args){
		handle_error(MALLOC);
		free(node);
		return (NULL);
	}
	count = 0;
	while (tokens && tokens->id == ARG)
	{ 
		node->args[count] = ft_strdup(tokens->value); // malloc
		if (!node->args[count])
		{
			handle_error(MALLOC);
			// free em args[i], args, node
			return (NULL);
		}
		count++;
		tokens = tokens->next;
	}
	node->args[count] = NULL;
	return (node);
}

t_ast	*parse_redir(t_token *tokens)
{
	t_ast	*node;
	t_token	*op;
	t_token	*left;
	t_token	*right;

	op = search_redir(&tokens);
	if (!op)
		return (parse_token(tokens));
	node = new_node(op->id);
	left = get_left_leg(op);
	right = get_right_leg(op);
	op->prev = NULL;
	op->next = NULL;
	free(op);
	node->left = parse_and_or(left);
	node->right = parse_and_or(right);
	printf("node: %i\n", node->id);
	if (node->left) {
		printf("left: id %i", node->left->id);
		if (node->left->id == CMD)
			printf(", value %s", node->left->args[0]);
		printf("\n");
	}
	if (node->right) {
		printf("right: id %i", node->right->id);
		if (node->right->id == CMD)
			printf(", value %s", node->right->args[0]);
		printf("\n");
	}
	return (node);
}

t_ast	*parse_pipe(t_token *tokens)
{
	t_ast	*node;
	t_token	*op;
	t_token	*left;
	t_token	*right;

	op = search_pipe(&tokens);
	if (!op)
		return (parse_redir(tokens));
	node = new_node(op->id);
	left = get_left_leg(op);
	right = get_right_leg(op);
	op->prev = NULL;
	op->next = NULL;
	free(op);
	node->left = parse_and_or(left);
	node->right = parse_and_or(right);
	printf("node: %i\n", node->id);
	if (node->left) {
		printf("left: id %i", node->left->id);
		if (node->left->id == CMD)
			printf(", value %s", node->left->args[0]);
		printf("\n");
	}
	if (node->right) {
		printf("right: id %i", node->right->id);
		if (node->right->id == CMD)
			printf(", value %s", node->right->args[0]);
		printf("\n");
	}
	return (node);
}

t_ast	*parse_and_or(t_token *tokens)
{
	t_ast	*node;
	t_token	*op;
	t_token	*left;
	t_token	*right;

	op = search_and_or(&tokens);
	if (!op)
		return (parse_pipe(tokens));
	node = new_node(op->id);
	left = get_left_leg(op);
	right = get_right_leg(op);
	op->prev = NULL;
	op->next = NULL;
	free(op);
	node->left = parse_and_or(left);
	node->right = parse_and_or(right);
	printf("node: %i\n", node->id);
	if (node->left) {
		printf("left: id %i", node->left->id);
		if (node->left->id == CMD)
			printf(", value %s", node->left->args[0]);
		printf("\n");
	}
	if (node->right) {
		printf("right: id %i", node->right->id);
		if (node->right->id == CMD)
			printf(", value %s", node->right->args[0]);
		printf("\n");
	}
	return (node);
}



/*t_ast	*parse_token(t_token **tokens)
{
	t_ast	*node;
	int		count;
	

	if (!tokens || !*tokens || (*tokens)->id != ARG)
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
		node->args[count] = ft_strdup((*tokens)->value); // malloc
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

t_ast	*parse_redir(t_token **tokens)
{
	t_ast	*node;
	t_token	*op;
	t_token	*right;

	op = search_redir(tokens);
	if (!op)
		return (parse_token(tokens));
	node = new_node(op->id);
	right = cut_token_list(tokens, op);
	node->left = parse_and_or(tokens);
	node->right = parse_and_or(&right);
	printf("node: %i\n", node->id);
	if (node->left) {
		printf("left: id %i", node->left->id);
		if (node->left->id == CMD)
			printf(", value %s", node->left->args[0]);
		printf("\n");
	}
	if (node->right) {
		printf("right: id %i", node->right->id);
		if (node->right->id == CMD)
			printf(", value %s", node->right->args[0]);
		printf("\n");
	}
	return (node);
}

t_ast	*parse_pipe(t_token **tokens)
{
	t_ast	*node;
	t_token	*op;
	t_token	*right;

	op = search_pipe(tokens);
	if (!op)
		return (parse_redir(tokens));
	node = new_node(op->id);
	right = cut_token_list(tokens, op);
	node->left = parse_and_or(tokens);
	node->right = parse_and_or(&right);
	printf("node: %i\n", node->id);
	if (node->left) {
		printf("left: id %i", node->left->id);
		if (node->left->id == CMD)
			printf(", value %s", node->left->args[0]);
		printf("\n");
	}
	if (node->right) {
		printf("right: id %i", node->right->id);
		if (node->right->id == CMD)
			printf(", value %s", node->right->args[0]);
		printf("\n");
	}
	return (node);
}

t_ast	*parse_and_or(t_token **tokens)
{
	t_ast	*node;
	t_token	*op;
	t_token	*right;

	op = search_and_or(tokens);
	if (!op)
		return (parse_pipe(tokens));
	node = new_node(op->id);
	right = cut_token_list(tokens, op);
	node->left = parse_and_or(tokens);
	node->right = parse_and_or(&right);
	printf("node: %i\n", node->id);
	if (node->left) {
		printf("left: id %i", node->left->id);
		if (node->left->id == CMD)
			printf(", value %s", node->left->args[0]);
		printf("\n");
	}
	if (node->right) {
		printf("right: id %i", node->right->id);
		if (node->right->id == CMD)
			printf(", value %s", node->right->args[0]);
		printf("\n");
	}
	return (node);
}*/

t_ast	*parser(t_token *tokens)
{
	t_ast	*root;
	t_token	*curr;

	printf("parser\n");
	curr = tokens;
	while (curr)
	{
		if (!check_syntax(curr))
			handle_error(SYNTAX); // retornar comando para o usuário
		curr = curr->next;
	}
	root = parse_and_or(tokens);
	if (!root)
		return (NULL);
	return (root);
}

/*
// build tree
t_ast	*build_tree(t_token *tokens)
{
	t_ast	*node;
	t_token	*op;

	op = search_and_or(tokens);
	if (op)
		// parse_and_or
	op = search_pipe(tokens);
	if (op)
		// parse_pipe
	op = search_redir(tokens);
	if (op)
		// parse_redir
	// parse_token
}
*/