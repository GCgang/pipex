/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:36:14 by hyeoan            #+#    #+#             */
/*   Updated: 2023/03/05 11:51:52 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	initialize(t_arg *pipex, int argc, char **argv, char **envp)
{
	if (argc < 5)
		exit_ctl(pipex, "argc error", 1);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		pipex->here_doc = 1;
		pipex->cmd_cnt = argc - 4;
	}
	else
	{
		pipex->here_doc = 0;
		pipex->cmd_cnt = argc - 3;
	}
	pipex->tot_pipe_cnt = pipex->cmd_cnt - 1;
	pipex->path = get_path(pipex, envp);
	pipex->cmds = get_cmds(pipex, argc, argv);
	if (pipex->cmds == NULL)
	{
		free_path(pipex->path);
		exit_ctl(pipex, "get_cmds error", 1);
	}
}

void	excute(t_arg *pipex, int argc, char **argv)
{
	int		idx;
	pid_t	pid;

	idx = -1;
	while (++idx < pipex->cmd_cnt)
	{
		if (idx % 2 == 0)
			if (pipe(pipex->even_fd) == -1)
				exit_ctl(pipex, "pipe error", 2);
		if (idx % 2 == 1)
			if (pipe(pipex->odd_fd) == -1)
				exit_ctl(pipex, "pipe error", 2);
		pid = fork();
		if (pid == -1)
			exit_ctl(pipex, "fork error", 2);
		else if (pid == 0)
			child_process(pipex, idx, argc, argv);
		else
			parent_process(pipex, idx);
	}
	while (idx--)
		waitpid(-1, NULL, 0);
}

void	finalize(t_arg *pipex)
{
	free_path(pipex->path);
	free_cmds(pipex->cmds);
}

void	exit_ctl(t_arg *pipex, char *errmsg, int exit_flag)
{
	if (exit_flag == 1)
	{
		perror(errmsg);
		exit(1);
	}
	if (exit_flag == 2)
	{
		perror(errmsg);
		finalize(pipex);
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_arg	pipex;

	initialize(&pipex, argc, argv, envp);
	excute(&pipex, argc, argv);
	finalize(&pipex);
	return (0);
}
