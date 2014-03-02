/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 12:21:39 by rbenjami          #+#    #+#             */
/*   Updated: 2013/12/24 13:37:27 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	unsigned int	ini;
	int				i;
	int				save;

	ini = 0;
	while (s1[ini] != '\0' && ini < n)
	{
		i = 0;
		save = ini;
		while (s1[ini] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && ini < n)
		{
			i++;
			ini++;
		}
		ini = save;
		if (s2[i] == '\0')
			return ((char*)&s1[ini]);
		else
			ini++;
	}
	return (NULL);
}
