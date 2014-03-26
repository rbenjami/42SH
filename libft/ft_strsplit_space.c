/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/01 13:46:34 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/26 18:32:27 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_words(char const *str)
{
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i])
		{
			while (str[i] && !(str[i] == ' ' || str[i] == '\t'))
				i++;
			size++;
		}
	}
	return (size);
}

char			**ft_strsplit_space(char *str)
{
	char	**tab;
	size_t	size;
	int		i;
	int		start;

	if ((size = ft_words(str)) == 0)
		return (NULL);
	if (!str || !(tab = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	i = 0;
	size = 0;
	while (str[i])
	{
		if ((str[i] == ' ' || str[i] == '\t'))
			i++;
		else
		{
			start = i;
			while (str[i] && !(str[i] == ' ' || str[i] == '\t'))
				i++;
			tab[size++] = ft_strsub(str, start, i - start);
		}
	}
	tab[size] = '\0';
	return (tab);
}
