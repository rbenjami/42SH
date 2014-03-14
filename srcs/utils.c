/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 12:25:29 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/14 12:49:55 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		close_pfd(int pfd[2])
{
	close(pfd[0]);
	close(pfd[1]);
}

void		dup_close(int *pfd, int *pfd_old, int b)
{
	if (pfd_old && b)
	{
		close(pfd_old[b]);
		close(!b);
		dup2(pfd_old[!b], !b);
	}
	close(pfd[!b]);
	close(b);
	dup2(pfd[b], b);
}
