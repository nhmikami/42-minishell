/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:45:20 by naharumi          #+#    #+#             */
/*   Updated: 2025/04/02 16:28:14 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(char *error)
{
	printf("%s\n", error);
	//free_all(minishell);
	exit(EXIT_FAILURE);
}

int	print_error(int error, int res_num, char *command, char *arg)
{
	if (error == INVALID_OPTION)
		printf("minishell: %s: %s: invalid option\n", command, arg);
	if (error == INVALID_ARG)
		printf("minishell: %s: %s: doesn't accept arguments\n", command, arg);
	if (error == INVALID_ID)
		printf("minishell: %s: %s: not a valid identifier\n", command, arg);
	if (error == NUMERIC_ARG)
		printf("minishell: %s: %s: numeric argument required\n", command, arg);
	if (error == EXCEED_ARG)
		printf("minishell: %s: too many arguments\n", command);
	if (error == INVALID_FILE)
		printf("minishell: %s: %s: no such file or directory", command, arg);
	if (error == INVALID_PATH)
		printf("minishell: %s: invalid path\n", command);
	if (error == INVALID_CMD)
		printf("minishell: %s: command not found\n", command);
	if (error == EXECVE)
		printf("minishell: %s: could not execute command\n", command);
	if (error == INVALID_INPUT)
		printf("minishell: invalid input: doesn't accept %s\n", command);
	if (error == QUOTES)
		printf("minishell: invalid input: please close quotes\n");
	return (res_num);
}

void	free_all(t_data *minishell)
{
	free_lev(minishell->lev);
	deallocate_mem(minishell->input);
	deallocate_mem(minishell);
	//fazer free token e ast
}

int	main(int ac, char **av, char **ev)
{
	(void)av;
	if (ac != 1)
		handle_error(USAGE);
	if (!ev)
		handle_error(EV);
	start(ev);
	return (0);
}
