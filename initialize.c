/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:59:37 by hyeoan            #+#    #+#             */
/*   Updated: 2023/03/05 11:24:07 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(t_arg *pipex, char **envp)
{
	char	**path;

	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		(*envp)++;
	if (*envp == NULL)
		exit_ctl(pipex, "envp error", 1);
	path = ft_split((*envp + 5), ':');
	if (path == NULL)
		exit_ctl(pipex, "get_path error", 1);
	return (path);
}

char	***get_cmds(t_arg *pipex, int argc, char **argv)
{
	char	***cmds;
	char	**cmd;
	int		i;
	int		j;

	cmds = (char ***)malloc(sizeof(char **) * (pipex->cmd_cnt + 1));
	if (cmds == NULL)
		return (NULL);
	if (pipex->here_doc == 1)
		i = 2;
	else
		i = 1;
	j = 0;
	while (++i < argc - 1)
	{
		cmd = ft_split(argv[i], ' ');
		if (cmd == NULL)
		{
			free_3d(cmds, pipex->cmd_cnt + 1);
			return (NULL);
		}
		cmds[j++] = cmd;
	}
	cmds[j] = NULL;
	return (cmds);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((*s1 != '\0' && *s1 == *s2) && i < n)
	{
		++s1;
		++s2;
		++i;
	}
	if (i == n)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
