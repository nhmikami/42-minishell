#include "minishell.h"

void    add_fd_list(t_data *minishell, int fd)
{
    t_fd_list   *new_node;

    new_node = malloc(sizeof(t_fd_list));
    new_node->fd = fd;

	// if (minishell->fd_list == NULL)
	// {
	// 	minishell->fd_list = new_node;
	// 	return ;
	// }

	new_node->next = minishell->fd_list;
	minishell->fd_list = new_node;
}

void	clear_fd_list(t_data *minishell)
{
	t_fd_list	*tmp;
	t_fd_list	*tmp2;

	tmp = minishell->fd_list;
	while (tmp)
	{
		tmp2 = tmp->next;
		close(tmp->fd);
		free(tmp);
		tmp = tmp2;
	}
	minishell->fd_list = NULL;
}
