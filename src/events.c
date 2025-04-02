/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:28:39 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/17 15:48:30 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_postorder(t_ast *node)
{
	if (!node)
		return;
	print_postorder(node->left);
	print_postorder(node->right);
	printf("Node ID: %d\n", node->id);
	if (node->left) {
		printf("left: id %i", node->left->id);
		if (node->left->id == ARG)
			printf(", value %s", node->left->args[0]);
		printf("\n");
	}
	if (node->right) {
		printf("right: id %i", node->right->id);
		if (node->right->id == ARG)
			printf(", value %s", node->right->args[0]);
		printf("\n");
	}
}

void	execute(t_data *minishell)
{
	t_token *tokens;
	t_ast	*root;

	while (1)
	{
		// signals
		minishell->input = get_input(minishell); // dar free na lista linkada
		if (!minishell->input)
			handle_error(INPUT);
		tokens = tokenizer(minishell->input);
		if (!tokens)
			handle_error(MALLOC);
		if (!check_syntax(tokens))
			handle_error(SYNTAX);
		root = build_tree(tokens);
		if (!root)
			handle_error(MALLOC);

		printf("\nparser\n");
		print_postorder(root);

		minishell->token = &tokens;
		minishell->root = &root;
		// execute

		clear_mem();
	}
}

void	finish(t_data *minishell)
{
	free_all(minishell);
	exit(EXIT_SUCCESS);
}

void	start(char **ev)
{
	t_data *minishell;

	minishell = init(ev); // copiar env
	execute(minishell);
	finish(minishell);
}
