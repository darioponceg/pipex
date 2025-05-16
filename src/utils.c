/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dponce <dponce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:29:39 by dponce            #+#    #+#             */
/*   Updated: 2025/05/15 22:42:32 by dponce           ###   ########.fr       */
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

void	exit_error_success(char *message)
{
	print_error(message);
	exit(EXIT_SUCCESS);
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
