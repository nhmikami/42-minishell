/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:45:00 by naharumi          #+#    #+#             */
/*   Updated: 2025/05/06 18:45:00 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_write(char *delimiter, int fd)
{
	char	*line;

	if (fd == -1)
		handle_error(TEMP_ERR);
	while (1)
	{
		line = readline("> ");
		if (!line && g_signal == SIGINT)
		{
			free(line);
			return ;
		}
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	return ;
}

static char	*generate_path(t_data *minishell)
{
	char	*num;
	char	*path;

	num = ft_itoa(minishell->heredoc_num);
	path = concatenate("heredoc", num, ".txt");
	minishell->heredoc_num++;
	return (path);
}

void	parse_heredoc(t_data *minishell, t_token *op)
{
	char	*path;
	int		fd;

	path = generate_path(minishell);
	if (!path)
		handle_error(MALLOC);
	fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	heredoc_signal();
	heredoc_write(op->next->value, fd);
	close(fd);
	interactive_signal();
	dup2(minishell->fd_bk[0], STDIN_FILENO);
	deallocate_mem(op->next->value);
	op->next->value = ft_strdup(path);
	return ;
}

void	remove_heredoc_files(t_data *minishell)
{
	char	*num;
	char	*file_name;

	while (minishell->heredoc_num >= 0)
	{
		num = ft_itoa(minishell->heredoc_num);
		file_name = concatenate("heredoc", num, ".txt");
		unlink(file_name);
		minishell->heredoc_num--;
	}
}
