/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dponce <dponce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 18:13:14 by dponce            #+#    #+#             */
/*   Updated: 2025/05/20 17:13:10 by dponce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path_from_envp(char **envp)
{
	int	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static void	open_files(t_pipex *data, char **argv)
{
	data->infile_fd = open(argv[1], O_RDONLY);
	data->infile_non_exist = 0;
	if (data->infile_fd < 0)
	{
		perror(argv[1]);
		data->infile_non_exist = 1;
	}
	data->outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile_fd < 0)
		perror(argv[4]);
}

void	init_pipex(t_pipex *data, char **argv, char **envp)
{
	char	*path_line;

	open_files(data, argv);
	data->envp = envp;
	data->cmd1_args = ft_split(argv[2], ' ');
	if (!data->cmd1_args)
		exit_error_cleanup(data, "Error split cmd1", EXIT_FAILURE);
	data->cmd2_args = ft_split(argv[3], ' ');
	if (!data->cmd2_args)
		exit_error_cleanup(data, "Error split cmd2", EXIT_FAILURE);
	path_line = get_path_from_envp(data->envp);
	if (!path_line)
		exit_error_cleanup(data, "Error. PATH not found in evnp", EXIT_FAILURE);
	data->cmd_path = ft_split(path_line, ':');
	if (!data->cmd_path)
		exit_error_cleanup(data, "Error split PATH", EXIT_FAILURE);
}
