/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:40:51 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/13 19:04:35 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_data *minishell)
{
	char	**arg;
	int		res;

	arg = ft_split(minishell->input, ' ');
	res = is_builtin(minishell, arg);
	if (res > 0)
		handle_error(BUILTIN);
	if (res == -1)
		printf("not builtin command \n");
}

// void	execute(t_data *minishell)
// {
// 	char	**arg;
// 	int		res;
// 	pid_t	pid;
// 	int		status;
// 	char	*cmd_path;

// 	arg = ft_split(minishell->input, ' ');
// 	res = is_builtin(minishell, arg);
// 	if (res > 0)
// 		handle_error(BUILTIN);
// 	else if (res == 0)
// 		return ;
// 	pid = fork();
// 	if (pid == 0) // Child process
// 	{
// 		cmd_path = find_command_path(arg[0], minishell->lev); // Find executable path
// 		if (!cmd_path)
// 		{
// 			fprintf(stderr, "minishell: command not found: %s\n", arg[0]);
// 			exit(127); // Exit with error code
// 		}
// 		execve(cmd_path, arg, minishell->lev); // Execute command
// 		perror("execve"); // If execve fails
// 		exit(1);
// 	}
// 	else if (pid < 0) // Fork failed
// 		perror("fork");
// 	else // Parent process
// 		waitpid(pid, &status, 0); // Wait for child to finish
// }
