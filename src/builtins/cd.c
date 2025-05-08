/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:35:01 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/08 16:12:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_pwds(t_lev *lev)
{
	t_lev	*pwd;
	t_lev	*old_pwd;
	char	*path;

	pwd = findlev(lev, "PWD");
	old_pwd = findlev(lev, "OLDPWD");
	if (!pwd || !old_pwd)
		handle_error(EV_NOTFOUND);
	path = ft_calloc(1024, sizeof(char));
	if (!path)
		handle_error(MALLOC);
	deallocate_mem(old_pwd->value);
	old_pwd->value = pwd->value;
	getcwd(path, 1024);
	pwd->value = ft_strdup(path);
	deallocate_mem(path);
	return (0);
}

int	cd(t_lev **lev, char **args)
{
	int	res;
	int	flag;

	flag = hasflag(args);
	if (flag)
		return (print_error(INVALID_OPTION, 2, "cd", args[flag]));
	if (!args[1])
		res = chdir(getenv("HOME"));
	else if (args[2] && ft_strlen(args[2]) > 0)
		return (print_error(EXCEED_ARG, 1, "cd", NULL));
	else
		res = chdir(args[1]);
	if (!res)
		return (update_pwds(*lev));
	else
		return (print_error(INVALID_FILE, 1, "cd", args[1]));
}
