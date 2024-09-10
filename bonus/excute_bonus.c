/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:52:32 by hyeoan            #+#    #+#             */
/*   Updated: 2023/03/05 11:51:27 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	parent_process(t_arg *pipex, int idx)
{
	if (idx == 0)
		close(pipex->even_fd[1]);
	else if (idx == pipex->tot_pipe_cnt && ((idx % 2) == 1))
	{
		close(pipex->even_fd[0]);
		close_pipe(pipex->odd_fd);
	}
	else if (idx == pipex->tot_pipe_cnt && ((idx % 2) == 0))
	{
		close(pipex->odd_fd[0]);
		close_pipe(pipex->even_fd);
	}
	else
	{
		if (idx % 2 == 1)
		{
			close(pipex->even_fd[0]);
			close(pipex->odd_fd[1]);
		}
		else if (idx % 2 == 0)
		{
			close(pipex->even_fd[1]);
			close(pipex->odd_fd[0]);
		}
	}
}

void	child_process(t_arg *pipex, int idx, int argc, char **argv)
{
	if (idx == 0)
		init_infile(pipex, idx, argv);
	else if (idx == pipex->tot_pipe_cnt)
		init_outfile(pipex, idx, argc, argv);
	else
	{
		if (idx % 2 == 1)
		{
			dup2(pipex->even_fd[0], STDIN_FILENO);
			close(pipex->even_fd[0]);
			dup2(pipex->odd_fd[1], STDOUT_FILENO);
			close(pipex->odd_fd[1]);
			close(pipex->odd_fd[0]);
		}
		else if (idx % 2 == 0)
		{
			dup2(pipex->odd_fd[0], STDIN_FILENO);
			close(pipex->odd_fd[0]);
			dup2(pipex->even_fd[1], STDOUT_FILENO);
			close(pipex->even_fd[1]);
			close(pipex->even_fd[0]);
		}
	}
	run_execve(pipex, idx);
}

void	run_execve(t_arg *pipex, int idx)
{
	char	*path_cmd;

	path_cmd = check_cmd(pipex, idx);
	if (path_cmd == NULL)
		exit_ctl(pipex, "cmd error", 2);
	execve(path_cmd, pipex->cmds[idx], NULL);
}

char	*check_cmd(t_arg *pipex, int idx)
{
	int		i;
	char	*cmd;
	char	*temp;

	i = -1;
	temp = ft_strjoin("/", pipex->cmds[idx][0]);
	while (pipex->path[++i] != NULL)
	{
		cmd = ft_strjoin(pipex->path[i], temp);
		if (access(cmd, X_OK) == 0)
			return (cmd);
		free(cmd);
	}
	free(temp);
	return (NULL);
}

void	close_pipe(int *pipe)
{
	close(pipe[0]);
	close(pipe[1]);
}
