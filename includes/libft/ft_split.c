/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:43:40 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/14 15:21:11 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	mini_strlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static int	mini_count_words(char const *s, char c)
{
	int	i;
	int	words;

	i = 1;
	words = 0;
	if (!s)
		return (0);
	if (s[0] != c)
		words++;
	while (s[i])
	{
		if (s[i - 1] == c && s[i] != c)
			words++;
		i++;
	}
	return (words);
}

static char	*make_word(char const *s, char c, char **splited, int index)
{
	int		i;
	int		len;
	char	*word;

	i = 0;
	len = mini_strlen(s, c);
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
	{
		while (index)
		{
			free(splited[index - 1]);
			index--;
		}
		free(splited);
		return (NULL);
	}
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static	char	**spliter(char **splited, char const *s, char c)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (s[0] != c)
	{
		splited[j] = make_word(s, c, splited, j);
		j++;
	}
	while (s[i])
	{
		if (s[i - 1] == c && s[i] != c)
		{
			splited[j] = make_word(s + i, c, splited, j);
			j++;
		}
		i++;
	}
	splited[j] = NULL;
	return (splited);
}

char	**ft_split(char const *s, char c)
{
	char	**splited;

	if (!s)
		return (NULL);
	if (*s == 0)
		return (ft_calloc(1, 8));
	splited = (char **)malloc((mini_count_words(s, c) + 1) * sizeof(char *));
	if (!splited)
		return (NULL);
	splited = spliter(splited, s, c);
	return (splited);
}
/*
int main (void)
{
	char	**strs;
	int		i;

	i = 0;
	strs = ft_split(0, '_');
	while (i < 1)
	{
		printf("%s, ", strs[i]);
		i++;
	}
}
*/
