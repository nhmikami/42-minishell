#include "minishell.h"

void    add_fd_list(t_data *minishell, int fd)
{
    t_fd_list   *new_node;

    new_node = malloc(sizeof(t_fd_list));
    new_node->fd = fd;

    if (!*minishell->fd_list)
	{
		*minishell->fd_list = new;
		return ;
	}
	new->next = *minishell->fd_list;
	*minishell->fd_list = new;
}
