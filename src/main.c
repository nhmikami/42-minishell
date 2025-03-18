/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:45:20 by naharumi          #+#    #+#             */
/*   Updated: 2025/03/13 19:02:52 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

void	free_all(t_data *minishell)
{
	free(minishell);
	//fazer free lev, token e ast
}

int main(int ac, char **av, char **ev)
{
	(void)av;
	if (ac != 1)
		handle_error(USAGE);
	if (!ev)
		handle_error(EV);
	//adicionar verificação de \ e ; aqui (retorna um erro)
	start(ev);
	return (0);
}
