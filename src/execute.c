/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dponce <dponce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:44:10 by dponce            #+#    #+#             */
/*   Updated: 2025/05/20 13:04:31 by dponce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_cmd_path(char *cmd, char **paths)
{
	char	*cmd_path;
	char	*temp;
	int		i;

	if (!cmd | !paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (NULL);
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

static void	child_process_1(t_pipex *data)
{
	char	*cmd1_path;

	if (data->infile_non_exist == 1)
	{
		close(data->pipe_fd[0]);
    	close(data->pipe_fd[1]);
		exit_cleanup(data, EXIT_SUCCESS);
	}
	if (dup2(data->infile_fd, STDIN_FILENO) < 0)
		exit_cleanup(data, EXIT_FAILURE);
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) < 0)
		exit_cleanup(data, EXIT_FAILURE);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	close(data->infile_fd);
	close(data->outfile_fd);
	cmd1_path = find_cmd_path(data->cmd1_args[0], data->cmd_path);
	if (!cmd1_path)
		exit_error_code_cleanup(data, data->cmd1_args[0], 127);
	execve(cmd1_path, data->cmd1_args, data->envp);
	free(cmd1_path);
	exit_cleanup(data, EXIT_FAILURE);
}

static void	child_process_2(t_pipex *data)
{
	char	*cmd2_path;

	if (dup2(data->pipe_fd[0], STDIN_FILENO) < 0)
		exit_cleanup(data, EXIT_FAILURE);
	if (dup2(data->outfile_fd, STDOUT_FILENO) < 0)
		exit_cleanup(data, EXIT_FAILURE);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	if (data->infile_fd >= 0)
		close(data->infile_fd);
	close(data->outfile_fd);
	cmd2_path = find_cmd_path(data->cmd2_args[0], data->cmd_path);
	if (!cmd2_path)
		exit_error_code_cleanup(data, data->cmd2_args[0], 127);
	execve(cmd2_path, data->cmd2_args, data->envp);
	free(cmd2_path);
	exit_cleanup(data, EXIT_FAILURE);
}

void	execute_pipex(t_pipex *data)
{
	int	status_cmd2;

	if (pipe(data->pipe_fd) < 0)
		exit_error_code_cleanup(data, "Error pipe", EXIT_FAILURE);
	data->pid1 = fork();
	if (data->pid1 < 0)
		exit_error_code_cleanup(data, "Error fork 1", EXIT_FAILURE);
	if (data->pid1 == 0)
		child_process_1(data);
	data->pid2 = fork();
	if (data->pid2 < 0)
		exit_error_code_cleanup(data, "Error fork 2", EXIT_FAILURE);
	if (data->pid2 == 0)
		child_process_2(data);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	waitpid(data->pid1, NULL, 0);
	waitpid(data->pid2, &status_cmd2, 0);
	data->exit_code = 1;
	if (WIFEXITED(status_cmd2))
		data->exit_code = WEXITSTATUS(status_cmd2);
}
