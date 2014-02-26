/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 13:28:19 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/26 16:10:49 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H
# define TRUE 1
# define FALSE 0

void	open_check(char *path);
int		ft_error(int error_num, char *name, int program_end);

#endif /* !SH_H */
