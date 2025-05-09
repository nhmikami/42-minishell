/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:35:30 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/18 12:08:24 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_data *minishell)
{
	char	path1[1024];
	char	*path2;

	if (!getcwd(path1, 1024))
	{
		path2 = get_key_value(*minishell->lev, "PWD");
		if (!path2)
			return (print_error(INVALID_PATH, 1, "pwd", NULL));
		else
			printf("%s\n", path2);
	}
	else
		printf("%s\n", path1);
	return (0);
}
