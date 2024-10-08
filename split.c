/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:49:39 by hyeoan            #+#    #+#             */
/*   Updated: 2023/03/05 11:14:39 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*free_2d(char	**str_arr)
{
	size_t	i;

	i = -1;
	while (str_arr[++i])
		free(str_arr[i]);
	free(str_arr);
	return (NULL);
}

size_t	ft_word_cnt(char *str, char charset)
{
	size_t	i;
	size_t	word;

	i = 0;
	word = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == charset)
			i++;
		if (str[i] != '\0')
			word++;
		while (str[i] != '\0' && str[i] != charset)
			i++;
	}
	return (word);
}

size_t	get_word_len(char *str, char charset)
{
	size_t	word_len;

	word_len = 0;
	while (str[word_len] != '\0' && (str[word_len] != charset))
		word_len++;
	return (word_len);
}

char	*put_word(char *str, char charset)
{
	char	*word;
	size_t	word_size;
	size_t	i;

	word_size = get_word_len(str, charset);
	word = (char *)malloc(sizeof(char) * (word_size + 1));
	if (word == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < word_size)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str, char charset)
{
	char	**str_arr;
	size_t	word;
	size_t	i;

	word = ft_word_cnt(str, charset);
	str_arr = (char **)malloc(sizeof(char *) * (word + 1));
	if (str_arr == NULL)
		return (NULL);
	i = 0;
	while (*str != '\0')
	{
		while (*str != '\0' && *str == charset)
			str++;
		if (*str != '\0')
		{
			str_arr[i] = put_word(str, charset);
			if (str_arr[i] == NULL)
				return (free_2d(str_arr));
			i++;
		}
		while (*str != '\0' && *str != charset)
			str++;
	}
	str_arr[i] = 0;
	return (str_arr);
}
