/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dponce <dponce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:33:18 by dponce            #+#    #+#             */
/*   Updated: 2025/05/12 19:23:08 by dponce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_pipex {
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fd[2];
	char	**cmd1_args;
	char	**cmd2_args;
	char	**cmd_path;
	char	**envp;
	pid_t	pid1;
	pid_t	pid2;
	int		exit_code;
}	t_pipex;

void	init_pipex(t_pipex *data, char **argv, char **envp);
void	execute_pipex(t_pipex *data);
void	cleanup_pipex(t_pipex *data);

void	print_error(char *message);
void	exit_error(char *message);
void	free_array(char **array);

#endif
