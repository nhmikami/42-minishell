/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:27:56 by marvin            #+#    #+#             */
/*   Updated: 2025/04/24 19:27:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	handle_error(char *error)
{
    printf("%s\n", error);
    clear_mem();
    exit(EXIT_FAILURE);
}
/* int	print_error(int error, int res_num, char *command, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	if (command)
	{
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": ", 2);
	}
	if ((error == INVALID_OPTION || error == INVALID_ARG
		|| error == INVALID_ID || error == NUMERIC_ARG
		|| error == INVALID_FILE))
	{
		if (arg)
		{
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": ", 2);
		}
	}
	if (error == INVALID_OPTION)
		ft_putstr_fd("invalid option\n", 2);
	else if (error == INVALID_ARG)
		ft_putstr_fd("doesn't accept arguments\n", 2);
	else if (error == INVALID_ID)
		ft_putstr_fd("not a valid identifier\n", 2);
	else if (error == NUMERIC_ARG)
		ft_putstr_fd("numeric argument required\n", 2);
	else if (error == EXCEED_ARG)
		ft_putstr_fd("too many arguments\n", 2);
	else if (error == INVALID_FILE)
		ft_putstr_fd("no such file or directory\n", 2);
	else if (error == INVALID_PATH)
		ft_putstr_fd("invalid path\n", 2);
	else if (error == INVALID_CMD)
		ft_putstr_fd("command not found\n", 2);
	else if (error == EXECVE)
		ft_putstr_fd("could not execute command\n", 2);
	else if (error == INVALID_INPUT)
	{
		ft_putstr_fd("invalid input: doesn't accept ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (error == QUOTES)
		ft_putstr_fd("invalid input: please close quotes\n", 2);
        update_exit_status(minishell, res_num);
    return (res_num);
}
 */

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
		printf("minishell: %s: %s: no such file or directory\n", command, arg);
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