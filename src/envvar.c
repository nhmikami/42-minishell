/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:18:29 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/14 15:51:07 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lev	*ft_findlev(t_lev *lev, char *key)
{
	int	len;

	len = ft_strlen(key);
	if (!lev)
		return (0);
	while (lev->next && ft_strncmp(lev->key, key, len))
	{
		if (!ft_strncmp(lev->key, key, len))
			return (lev);
		lev = lev->next;
	}
	return (NULL);
}
