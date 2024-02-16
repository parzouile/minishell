/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:36:16 by aschmitt          #+#    #+#             */
/*   Updated: 2023/11/14 17:39:28 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static char	*ft_line(char const *str, int a, int i)
{
	char	*line;
	int		j;

	j = 0;
	line = malloc(sizeof(char) * (i - a + 1));
	if (!line)
		return (NULL);
	while (a < i)
	{
		line[j++] = str[a++];
	}
	line[j] = 0;
	return (line);
}

static int	nb_word(char const *s, char c)
{
	int	i;
	int	a;
	int	nb;

	nb = 0;
	i = -1;
	while (s[++i])
	{
		a = i;
		while (s[i] && s[i] != c)
			i ++;
		if (a != i)
			nb ++;
		if (!s[i])
			return (nb);
	}
	return (nb);
}

static char	**ft_free(char **result, int n)
{
	while (n >= 0)
	{
		free(result[n]);
		n--;
	}
	free(result);
	return (NULL);
}

static char	**ft_tab(char **result, char const *s, char c)
{
	int	i;
	int	a;
	int	i_tab;

	i_tab = 0;
	i = -1;
	while (s[++i])
	{
		a = i;
		while (s[i] && s[i] != c)
			i ++;
		if (i != a)
		{
			result[i_tab++] = ft_line(s, a, i);
			if (!result[i_tab - 1])
				return (ft_free(result, i_tab - 1));
			result[i_tab] = 0;
		}
		if (!s[i])
			return (result);
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (s == NULL)
		return (NULL);
	result = (char **) malloc(sizeof(char *) * (nb_word(s, c) + 1));
	if (!result)
		return (NULL);
	result[0] = 0;
	result = ft_tab(result, s, c);
	return (result);
}
