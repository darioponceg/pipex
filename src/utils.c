/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dponce <dponce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:29:39 by dponce            #+#    #+#             */
/*   Updated: 2025/05/20 13:08:07 by dponce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *message)
{
	perror(message);
}

void	exit_error(char *message)
{
	print_error(message);
	exit(EXIT_FAILURE);
}

void	exit_error_code(char *message, int code)
{
	print_error(message);
	exit(code);
}

void	exit_error_code_cleanup(t_pipex *data, char *message, int code)
{
	perror(message);
	cleanup_pipex(data);
	exit(code);
}

void	exit_cleanup(t_pipex *data, int code)
{
	cleanup_pipex(data);
	exit(code);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	cleanup_pipex(t_pipex *data)
{
	if (data->cmd1_args)
		free_array(data->cmd1_args);
	if (data->cmd2_args)
		free_array(data->cmd2_args);
	if (data->cmd_path)
		free_array(data->cmd_path);
	if (data->infile_fd >= 0)
		close(data->infile_fd);
	if (data->outfile_fd >= 0)
		close(data->outfile_fd);
}
