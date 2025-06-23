/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:42:12 by naharumi          #+#    #+#             */
/*   Updated: 2025/06/23 19:45:44 by naharumi         ###   ########.fr       */
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

static void	print_error2(int error, char *cmd, char *arg)
{
	if (error == DIR_CMD)
		ft_printf_fd(2, "minishell: Is a directory\n");
	else if (error == INVALID_PERM)
		ft_printf_fd(2, "minishell: Permission denied\n");
	else if (error == AMBIGUOUS_REDIR)
		ft_printf_fd(2, "minishell: ambiguous redirect\n");
	else if (error == QUOTES)
		ft_printf_fd(2, "minishell: invalid input: please close quotes\n");
	else if (error == INVALID_INPUT)
		ft_printf_fd(2, "minishell: invalid input: doesn't accept %s\n", cmd);
	else if (error == SYNTAX)
		ft_printf_fd(2, "minishell: syntax error near unexpected token `%s'\n",
			arg);
}

int	print_error(int error, int res_num, char *cmd, char *arg)
{
	if (error == INVALID_OPTION)
		ft_printf_fd(2, "minishell: %s: %s: invalid option\n", cmd, arg);
	else if (error == INVALID_ARG)
		ft_printf_fd(2, "minishell: %s: %s: doesn't accept arguments\n",
			cmd, arg);
	else if (error == INVALID_ID)
		ft_printf_fd(2, "minishell: %s: %s: not a valid identifier\n", cmd, arg);
	else if (error == NUMERIC_ARG)
		ft_printf_fd(2, "minishell: %s: %s: numeric argument required\n",
			cmd, arg);
	else if (error == EXCEED_ARG)
		ft_printf_fd(2, "minishell: %s: too many arguments\n", cmd);
	else if (error == INVALID_FILE)
		ft_printf_fd(2, "minishell: %s: %s: No such file or directory\n",
			cmd, arg);
	else if (error == INVALID_PATH)
		ft_printf_fd(2, "minishell: %s: invalid path\n", cmd);
	else if (error == INVALID_CMD)
		ft_printf_fd(2, "minishell: %s: command not found\n", cmd);
	else if (error == EXECVE)
		ft_printf_fd(2, "minishell: %s: could not execute command\n", cmd);
	else
		print_error2(error, cmd, arg);
	return (res_num);
}
