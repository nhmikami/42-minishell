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
		ft_printf_fd(2, "minishell: %s: %s: No such file or directory\n", command, arg);
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
	if (error == SYNTAX)
		ft_printf_fd(2, "minishell: syntax error near unexpected token `%s'\n", arg);
	return (res_num);
}