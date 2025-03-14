/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:58:46 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/14 19:13:52 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validade_identifier(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '_' || ft_isalpha(str[i]))
	{
		while (str[i] && str[i] != '=' && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		if (str[i] == '=' || !str[i])
			return (1);
	}
	return (0);
}

int	exec_export(t_lev **lev, char **args)
{
	t_lev	*node;
	char	**key_value;

	if (!args[1] || !args[1][0])
		return (print_lev(lev)); //imprimir ordenado
	if (!validade_identifier(args[1]))
		handle_error(EXPORT_IDENTIFIER);
	key_value = ft_split(args[1], '=');
	node = ft_findlev(*lev, key_value[0]);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(key_value[1]);
	}
	else
	{
		node = ft_levnew(key_value, 1);
		ft_levadd_back(lev, node);
	}
	return (0);
}

int	exec_unset(t_lev **lev, char **args)
{
	int	res;
//verificar o que tem que dar erro qual erro
	if (!ft_isalnum(args[1]))
		handle_error(UNSET_PARAM);
	res = ft_levdel(lev, args[1]);
	if (res == 1)
		handle_error(UNSET_MATCH);
	if (res == 2)
		handle_error(UNSET_DEL);
	return (0);
}

int	exec_env(t_lev **lev, char **args)
{
	if (args[1])
		handle_error(ENV_ARG);
	return (print_lev(lev));
}

void exec_exit(t_data *minishell)
{
	//guarda numero até int max, dps faz conversao, só aceita 1 arg
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
}
*/