/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:40:59 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/13 16:45:16 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (!ft_strncmp(args[i], "-n", 2))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

int	exec_cd(char **args)
{
	//atualizar pwd e old pwd
	if (!args[1]) //verificar se precisa tratar isso
		return (chdir(getenv("HOME")));
	return (chdir(args[1]));
}

int	exec_pwd(void)
{
	char	path[1024];

	if (!getcwd(path, 1024))
		return (1);
	printf("%s\n", path);
	return (0);
}

int	exec_export(t_lev **lev, char **args)
{
	t_lev	*new;

	if (!args[1])
		return (print_lev(lev)); //só printar exportados
	//nao aceita exportar qualquer nome, tem que começar com _ ou letra
	new = ft_levnew(&args[1]);
	ft_levadd_back(lev, new);
	return (0);
}

// int	exec_unset(char **args)
// {
// 	//só aceita o nome da variavel 
// 	//verificar se pode deletar antes
// 	return (0);
// }

int	exec_env(t_lev **lev)
{
	return (print_lev(lev));
}

void exec_exit(t_data *minishell)
{
	free_all(minishell);
	exit(EXIT_SUCCESS);
}

int	is_builtin(t_data *minishell, char **args)
{
	if (!ft_strncmp(args[0], "echo", 4))
		return (exec_echo(args));
	if (!ft_strncmp(args[0], "cd", 2))
		return (exec_cd(args));
	if (!ft_strncmp(args[0], "pwd", 3))
		return (exec_pwd());
	if (!ft_strncmp(args[0], "export", 6))
		return (exec_export(minishell->lev, args));
	// if (!ft_strncmp(args[0], "unset", 5))
	// 	return (exec_unset(args));
	if (!ft_strncmp(args[0], "env", 3))
		return (exec_env(minishell->lev));
	if (!ft_strncmp(args[0], "exit", 4))
		exec_exit(minishell);
	return (-1);
}
