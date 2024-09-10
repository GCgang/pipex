/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:54:26 by hyeoan            #+#    #+#             */
/*   Updated: 2023/03/05 11:14:29 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_document(t_arg *pipex, char **argv)
{
	char	*line;
	char	*limiter;

	limiter = argv[2];
	while (1)
	{
		ft_putstr_fd("> ", 0);
		line = get_next_line(0);
		if (ft_strncmp(line, limiter, (ft_strlen(line) - 1)) == 0 || \
		line == NULL)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipex->in_file);
		free(line);
	}
	close(pipex->in_file);
}

void	init_infile(t_arg *pipex, int idx, char **argv)
{
	if (pipex->here_doc == 1)
	{
		pipex->in_file = open("temp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pipex->in_file == -1)
			perror("infile error");
		here_document(pipex, argv);
		pipex->in_file = open("temp", O_RDONLY);
	}
	else if (pipex->here_doc == 0)
	{
		pipex->in_file = open(argv[1], O_RDONLY);
	}
	if (pipex->in_file == -1)
		exit_ctl(pipex, "infile error", 2);
	close(pipex->even_fd[0]);
	dup2(pipex->in_file, STDIN_FILENO);
	close(pipex->in_file);
	dup2(pipex->even_fd[1], STDOUT_FILENO);
	close(pipex->even_fd[1]);
	run_execve(pipex, idx);
}

void	init_outfile(t_arg *pipex, int idx, int argc, char **argv)
{
	if (pipex->here_doc == 1)
		pipex->out_file = open(argv[argc - 1], \
										O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (pipex->here_doc == 0)
		pipex->out_file = open(argv[argc - 1], \
										O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->out_file == -1)
		perror("outfile error");
	if (idx % 2 == 1)
	{
		close(pipex->odd_fd[0]);
		close(pipex->odd_fd[1]);
		dup2(pipex->even_fd[0], STDIN_FILENO);
		close(pipex->even_fd[0]);
	}
	else if (idx % 2 == 0)
	{
		close(pipex->even_fd[0]);
		close(pipex->even_fd[1]);
		dup2(pipex->odd_fd[0], STDIN_FILENO);
		close(pipex->odd_fd[0]);
	}
	dup2(pipex->out_file, STDOUT_FILENO);
	close(pipex->out_file);
	run_execve(pipex, idx);
}
