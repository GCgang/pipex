/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:37:55 by hyeoan            #+#    #+#             */
/*   Updated: 2023/03/05 11:51:41 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strchr(char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*strarr;
	size_t	size;
	size_t	i;

	size = ft_strlen(s1) + ft_strlen(s2);
	strarr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (strarr == NULL)
		return (NULL);
	i = 0;
	size = 0;
	while (s1[i] != '\0')
		strarr[size++] = s1[i++];
	strarr[size] = '\0';
	i = 0;
	size = ft_strlen(strarr);
	while (s2[i] != '\0')
		strarr[size++] = s2[i++];
	strarr[size] = '\0';
	return (strarr);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*s_sub;
	size_t	s_len;
	size_t	i;
	size_t	size;

	s_len = ft_strlen(s);
	if (s_len >= start)
	{
		size = s_len - start;
		if (size >= len)
			size = len;
	}
	else
		size = 0;
	s_sub = (char *)malloc(sizeof(char) * size + 1);
	i = 0;
	if (s_sub == NULL)
		return (NULL);
	while (size-- && s[start] != '\0')
	{
		s_sub[i++] = s[start++];
	}
	s_sub[i] = '\0';
	return (s_sub);
}

void	remove_list(t_list *file_list)
{
	free(file_list->current->back_up);
	file_list->before->next = file_list->current->next;
	if (file_list->current == file_list->tail)
		file_list->tail = file_list->before;
	free(file_list->current);
	file_list->total_fd--;
	if (file_list->total_fd == 0)
		file_list->tail = NULL;
	else
		file_list->current = file_list->before->next;
}
