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

int	pwd(void)
{
	char	path[1024];

	if (!getcwd(path, 1024))
		return (print_error(INVALID_PATH, 1, "pwd", NULL));
	printf("%s\n", path);
	return (0);
}
