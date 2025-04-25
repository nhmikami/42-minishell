/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:45:20 by naharumi          #+#    #+#             */
/*   Updated: 2025/04/25 17:45:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(char *error)
{
	ft_printf_fd(2, "%s\n", error);
	//free_all(minishell);
	exit(EXIT_FAILURE);
}

int	print_error(int error, int res_num, char *command, char *arg)
{
	if (error == INVALID_OPTION)
		ft_printf_fd(2, "minishell: %s: %s: invalid option\n", command, arg);
	if (error == INVALID_ARG)
		ft_printf_fd(2, "minishell: %s: %s: doesn't accept arguments\n", command, arg);
	if (error == INVALID_ID)
		ft_printf_fd(2, "minishell: %s: %s: not a valid identifier\n", command, arg);
	if (error == NUMERIC_ARG)
		ft_printf_fd(2, "minishell: %s: %s: numeric argument required\n", command, arg);
	if (error == EXCEED_ARG)
		ft_printf_fd(2, "minishell: %s: too many arguments\n", command);
	if (error == INVALID_FILE)
		ft_printf_fd(2, "minishell: %s: %s: no such file or directory\n", command, arg);
	if (error == INVALID_PATH)
		ft_printf_fd(2, "minishell: %s: invalid path\n", command);
	if (error == INVALID_CMD)
		ft_printf_fd(2, "minishell: %s: command not found\n", command);
	if (error == EXECVE)
		ft_printf_fd(2, "minishell: %s: could not execute command\n", command);
	if (error == INVALID_INPUT)
		ft_printf_fd(2, "minishell: invalid input: doesn't accept %s\n", command);
	if (error == QUOTES)
		ft_printf_fd(2, "minishell: invalid input: please close quotes\n");
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
