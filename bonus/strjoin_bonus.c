/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:15:34 by hyeoan            #+#    #+#             */
/*   Updated: 2023/03/05 11:52:01 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strcat(char *dest, char *src)
{
	size_t	i;
	size_t	dest_len;

	i = 0;
	dest_len = ft_strlen(dest);
	while (src[i])
	{
		dest[dest_len++] = src[i++];
	}
	dest[dest_len] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*strarr;
	size_t	size;
	size_t	i;

	size = ft_strlen(s1) + ft_strlen(s2);
	strarr = (char *)malloc(size + 1);
	if (strarr == NULL)
		return (NULL);
	i = 0;
	strarr[0] = '\0';
	strarr = ft_strcat(strarr, s1);
	strarr = ft_strcat(strarr, s2);
	return (strarr);
}
