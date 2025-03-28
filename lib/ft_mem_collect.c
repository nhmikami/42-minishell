/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_collect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:08:19 by naharumi          #+#    #+#             */
/*   Updated: 2025/03/26 18:13:12 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	**get_memory_ptr(void)
{
	static t_list	*ptr;

	return (&ptr);
}

void	collect_mem(void *content)
{
	ft_lstadd_front(get_memory_ptr(), ft_lstnew(content));
}

void	deallocate_mem(void)
{
	// get_next_line(-1);
	ft_lstclear(get_memory_ptr(), &free);
}

void	*allocate_mem(size_t nmemb, size_t size)
{
	void	*p;

	p = ft_calloc(nmemb, size);
	collect_mem(p);
	return (p);
}