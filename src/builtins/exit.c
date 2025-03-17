/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:58:46 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/17 19:23:59 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	exec_exit(t_data *minishell, char **args)
{
	int	exit_num;
	int	flag;

	printf("exit\n");
	if (args[2])
		return (print_error(EXCEED_ARG, 1, "exit", NULL));
	if (!ft_isdigit(args[1]))
		return (print_error(NUMERIC_ARG, 2, "exit", args[1]));
	if ((flag = hasflag(args)))
		return (print_error(INVALID_OPTION, 3, "exit", args[flag]));
	if (args[1] < 0)
		exit_num = negative_exit_num(args[1]);
	else if (args[1] > 255)
		exit_num = big_exit_num(args[1]);
	else
		exit_num = args[1] - '0';
	//guardar exit_num em "$?"
	free_all(minishell);
	exit(EXIT_SUCCESS);
}

/*

static void	exit_print_error_message(char *message)
{
	int			i;
	int			length;
	char		*line;
	const char	*to_print[] = {RED"ERROR: "RST"exit: ", message, NULL};

	i = 0;
	length = 0;
	while (to_print[i])
		length += ft_strlen(to_print[i++]);
	line = malloc(sizeof(char) * (length + 1));
	i = 1;
	ft_strlcpy(line, to_print[0], length + 1);
	while (to_print[i])
	{
		ft_strlcat(line, to_print[i], length + 1);
		i++;
	}
	ft_putendl_fd(line, STDERR_FILENO);
	free(line);
}

int	exit_arg_valid(char *arg)
{
	int	i;

	i = 0;
	while (isspace(arg[i]))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
static void	exit_print_error_message(char *message)
{
	int			i;
	int			length;
	char		*line;
	const char	*to_print[] = {RED"ERROR: "RST"exit: ", message, NULL};

	i = 0;
	length = 0;
	while (to_print[i])
		length += ft_strlen(to_print[i++]);
	line = malloc(sizeof(char) * (length + 1));
	i = 1;
	ft_strlcpy(line, to_print[0], length + 1);
	while (to_print[i])
	{
		ft_strlcat(line, to_print[i], length + 1);
		i++;
	}
	ft_putendl_fd(line, STDERR_FILENO);
	free(line);
}

int	exit_arg_valid(char *arg)
{
	int	i;

	i = 0;
	while (isspace(arg[i]))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			exit_print_error_message("numeric argument required");
			return (0);
		}
		i++;
	}
static void	exit_print_error_message(char *message)
{
	int			i;
	int			length;
	char		*line;
	const char	*to_print[] = {RED"ERROR: "RST"exit: ", message, NULL};

	i = 0;
	length = 0;
	while (to_print[i])
		length += ft_strlen(to_print[i++]);
	line = malloc(sizeof(char) * (length + 1));
	i = 1;
	ft_strlcpy(line, to_print[0], length + 1);
	while (to_print[i])
	{
		ft_strlcat(line, to_print[i], length + 1);
		i++;
	}
	ft_putendl_fd(line, STDERR_FILENO);
	free(line);
}

int	exit_arg_valid(char *arg)
{
	int	i;

	i = 0;
	while (isspace(arg[i]))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			exit_print_error_message("numeric argument required");
			return (0);
		}
		i++;
	}
	return (1);
}

int	builtin_exit(char **argv, t_minishell *data)
{
	int		ret_code;
	int		args_num;
	char	*ret_code_str;

	ret_code = 0;
	args_num = 0;
	while (argv[args_num])
		args_num++;
	if (args_num > 2)
	{
		exit_print_error_message("too many arguments");
		return (1);
	}
	if (args_num == 1)
	{
		ret_code_str = search_value(data->envp_list, "?");
		ret_code = ft_atoi(ret_code_str);
		free(ret_code_str);
	}
	else if (!exit_arg_valid(argv[1]))
		ret_code = 2;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	g_signal = -1;
	return (ternary(args_num == 1, ret_code, \
		ternary(ret_code == 2, 2, ft_atoi(argv[1]))));
	return (1);
}

*/
