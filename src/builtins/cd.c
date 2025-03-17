/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:35:01 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/17 19:10:56 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_pwds(t_lev *lev)
{
	t_lev	*pwd;
	t_lev	*old_pwd;
	char	*path;

	pwd = findlev(lev, "PWD");
	old_pwd = findlev(lev, "OLD_PWD");
	path = ft_calloc(1024, sizeof(char));
	if (!path)
		handle_error(MALLOC);
	free(old_pwd->value);
	old_pwd->value = pwd->value;
	getcwd(path, 1024);
	pwd->value = path;
	return (0);
}

int	cd(t_lev **lev, char **args)
{
	int	res;
	int	flag;

	if ((flag = hasflag(args)))
		return (print_error(INVALID_OPTION, 2, "cd", args[flag]));
	if (!args[1])
		res = chdir(getenv("HOME"));
	else
		res = chdir(args[1]);
	if (!res)
		return (update_pwds(*lev));
	else
		return (print_error(INVALID_FILE, 1, "cd", args[1]));
}
