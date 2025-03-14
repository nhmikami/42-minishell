/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:40:59 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/14 16:04:12 by cayamash         ###   ########.fr       */
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

int	update_pwds(t_lev *lev)
{
	t_lev	*pwd;
	t_lev	*old_pwd;

	pwd = ft_findlev(lev, "PWD");
	old_pwd = ft_findlev(lev, "OLD_PWD");

	//AGORA ATUALIZA AI!! ??
}

int	exec_cd(t_lev **lev, char **args)
{
	int	res;

	if (!args[1]) //verificar se precisa tratar isso
		res = chdir(getenv("HOME"));
	else
		res = chdir(args[1]);
	if (!res)
		return (update_pwds(*lev));
	return (res);
}

int	exec_pwd(void)
{
	char	path[1024];

	if (!getcwd(path, 1024))
		return (1);
	printf("%s\n", path);
	return (0);
}



int	is_builtin(t_data *minishell, char **args)
{
	if (!ft_strncmp(args[0], "echo", 4))
		return (exec_echo(args));
	if (!ft_strncmp(args[0], "cd", 2))
		return (exec_cd(minishell->lev, args));
	if (!ft_strncmp(args[0], "pwd", 3))
		return (exec_pwd());
	if (!ft_strncmp(args[0], "export", 6))
		return (exec_export(minishell->lev, args));
	// if (!ft_strncmp(args[0], "unset", 5))
	// 	return (exec_unset(args));
	if (!ft_strncmp(args[0], "env", 3))
		return (exec_env(minishell->lev, args));
	if (!ft_strncmp(args[0], "exit", 4))
		exec_exit(minishell);
	return (-1);
}
