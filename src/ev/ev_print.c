/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:20:48 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/02 16:11:44 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_lev(t_lev **lev, int ordered)
{
	t_lev	*node;

	node = *lev;
	while (node)
	{
		if (ordered)
			printf("declare -x %s=%s\n", node->key, node->value);
		else
			printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
	return (0);
}

t_lev	**copy_lev(t_data *minishell)
{
	t_lev	**lev_ord;
	t_lev	*new_node;
	t_lev	*temp;
	char	*arr_ev[3];

	lev_ord = allocate_mem(1, sizeof(t_lev *));
	if (!lev_ord)
		handle_error(MALLOC);
	*lev_ord = NULL;
	temp = *minishell->lev;
	while (temp)
	{
		arr_ev[0] = temp->key;
		arr_ev[1] = temp->value;
		arr_ev[2] = NULL;
		new_node = new_lev(arr_ev);
		levadd_back(lev_ord, new_node);
		temp = temp->next;
	}
	return (lev_ord);
}

int	swap_lev(t_lev **head, t_lev *a, t_lev *b)
{
	t_lev	*a_prev;
	t_lev	*b_next;

	if (!a || !b || a == b)
		return (0);
	if (a->prev)
		a->prev->next = b;
	else
		*head = b;
	if (b->next)
		b->next->prev = a;
	a_prev = a->prev;
	b_next = b->next;
	a->prev = b;
	a->next = b_next;
	b->prev = a_prev;
	b->next = a;
	return (1);
}

t_lev	**sort_lev(t_lev **lev_ord, int ev_num)
{
	int		swap;
	int		len;
	t_lev	*curr;

	if (!lev_ord || !*lev_ord || ev_num < 2)
		return (lev_ord);
	while (1)
	{
		swap = 0;
		curr = *lev_ord;
		while (curr && curr->next)
		{
			len = ft_strlen(curr->key);
			if (ft_strncmp(curr->key, curr->next->key, len) > 0)
				swap = swap_lev(lev_ord, curr, curr->next);
			curr = curr->next;
		}
		if (swap == 0)
			break ;
	}
	return (lev_ord);
}

int	print_lev_ord(t_data *minishell)
{
	t_lev	**lev_ord;
	int		res;

	lev_ord = copy_lev(minishell);
	lev_ord = sort_lev(lev_ord, minishell->ev_num);
	res = print_lev(lev_ord, 1);
	free_lev(lev_ord);
	return (res);
}
