/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dponce-g <dponce-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:15:31 by dponce-g          #+#    #+#             */
/*   Updated: 2024/12/18 18:42:15 by dponce-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	count;
	int	is_word;

	count = 0;
	is_word = 0;
	while (*s)
	{
		if (*s == c)
			is_word = 0;
		else if (is_word == 0)
		{
			is_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static int	ft_len_word(const char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static void	ft_free_split(char **array, int words_count)
{
	int		i;

	if (array == NULL)
		return ;
	i = 0;
	while (i < words_count)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	**ft_fill_split(char **d, const char *s, char c)
{
	int		i;
	int		len;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		len = ft_len_word(s, c);
		d[i] = malloc(len + 1);
		if (d[i] == NULL)
		{
			ft_free_split(d, i);
			return (NULL);
		}
		ft_strlcpy(d[i], s, len + 1);
		s += len;
		i++;
	}
	d[i] = NULL;
	return (d);
}

char	**ft_split(char const *s, char c)
{
	char	**d;
	int		n_words;

	n_words = ft_count_words(s, c);
	d = malloc((n_words + 1) * sizeof(char *));
	if (!d)
		return (NULL);
	d = ft_fill_split(d, s, c);
	return (d);
}
