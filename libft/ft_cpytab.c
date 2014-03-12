/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpytab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 14:58:18 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/12 15:10:54 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_cpytab(char **tab, int lenth)
{
	char	**new_tab;
	int		i;
	int		tablen;

	i = 0;
	tablen = ft_tablen(tab);
	new_tab = (char **)ft_memalloc(sizeof(char *) * lenth + 1);
	while (i < tablen)
	{
		new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	return (new_tab);
}
