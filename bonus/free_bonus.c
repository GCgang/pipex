/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:49:43 by hyeoan            #+#    #+#             */
/*   Updated: 2023/03/05 11:51:31 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_3d(char ***cmds, int alloc_space)
{
	int	i;

	i = -1;
	while (++i < alloc_space)
		free(cmds[i]);
}

void	free_path(char **path)
{
	int	i;

	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
}

void	free_cmds(char ***cmds)
{
	int	i;
	int	j;

	i = -1;
	while (cmds[++i])
	{
		j = -1;
		while (cmds[i][++j])
			free(cmds[i][j]);
		free(cmds[i]);
	}
	free(cmds);
}
