/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dponce <dponce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 18:13:14 by dponce            #+#    #+#             */
/*   Updated: 2025/05/11 19:44:33 by dponce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_paht_from_envp(char **envp)
{
	int	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PAHT=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	init_pipex(t_pipex *data, char **argv, char **envp)
{
	char	*path_line;
	
	data->infile_fd = open(argv[1], O_RDONLY);
	if (data->infile_fd < 0)
		exit_error("Error infile");
	data->outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile_fd < 0)
		exit_error("Error outfile");
	data->envp = envp;
	data->cmd1_args = ft_split(argv[2], ' ');
	if (!data->cmd1_args)
		exit_error("Error split cmd1");
	data->cmd2_args = ft_split(argv[3], ' ');
	if (!data->cmd2_args)
		exit_error("Error split cmd2");
	path_line = get_path_from_envp(data->envp);
	if (!path_line)
		exit_error("Error. PATH not found in evnp");
	data->cmd_path = ft_split(path_line, ':');
	if (!data->cmd_path)
		exit_error("Error split PATH");
}
