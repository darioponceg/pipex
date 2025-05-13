/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dponce-g <dponce-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:03:38 by dponce            #+#    #+#             */
/*   Updated: 2025/05/13 20:23:53 by dponce-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc != 5)
	{
		write(STDERR_FILENO,
			"Error. Use: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", 49);
		return (1);
	}
	data.infile_fd = -1;
	data.outfile_fd = -1;
	init_pipex(&data, argv, envp);
	execute_pipex(&data);
	cleanup_pipex(&data);
	return (data.exit_code);
}
