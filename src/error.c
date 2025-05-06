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
	clear_mem();
	exit(EXIT_FAILURE);
}

int	print_command_error(int res, char *args)
{
	if (res == -1)
		return (print_error(INVALID_PERM, 126, NULL, NULL));
	else if (res == -2)
		return (print_error(INVALID_FILE, 127, NULL, NULL));
	else if (res == -3)
		return (print_error(DIR_CMD, 126, NULL, NULL));
	else
		return (print_error(INVALID_CMD, 127, args, NULL));
}

int	print_error(int error, int res_num, char *command, char *arg)
{
	if (error == INVALID_OPTION)
		ft_printf_fd(2, "minishell: %s: %s: invalid option\n", command, arg);
	else if (error == INVALID_ARG)
		ft_printf_fd(2, "minishell: %s: %s: doesn't accept arguments\n", command, arg);
	else if (error == INVALID_ID)
		ft_printf_fd(2, "minishell: %s: %s: not a valid identifier\n", command, arg);
	else if (error == NUMERIC_ARG)
		ft_printf_fd(2, "minishell: %s: %s: numeric argument required\n", command, arg);
	else if (error == EXCEED_ARG)
		ft_printf_fd(2, "minishell: %s: too many arguments\n", command);
	else if (error == INVALID_FILE)
		ft_printf_fd(2, "minishell: %s: %s: No such file or directory\n", command, arg);
	else if (error == INVALID_PATH)
		ft_printf_fd(2, "minishell: %s: invalid path\n", command);
	else if (error == INVALID_CMD)
		ft_printf_fd(2, "minishell: %s: command not found\n", command);
	else if (error == EXECVE)
		ft_printf_fd(2, "minishell: %s: could not execute command\n", command);
	else if (error == INVALID_INPUT)
		ft_printf_fd(2, "minishell: invalid input: doesn't accept %s\n", command);
	else if (error == QUOTES)
		ft_printf_fd(2, "minishell: invalid input: please close quotes\n");
	else if (error == SYNTAX)
		ft_printf_fd(2, "minishell: syntax error near unexpected token `%s'\n", arg);
	else if (error == DIR_CMD)
		ft_printf_fd(2, " Is a directory\n");
	else if (error == INVALID_PERM)
		ft_printf_fd(2, " Permission denied\n");
	else if (error == AMBIGUOUS_REDIR)
		ft_printf_fd(2, "minishell: ambiguous redirect\n");
	return (res_num);
}
