/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 13:28:19 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/27 11:01:28 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H
# define TRUE 1
# define FALSE 0
# include <libft.h>

enum	e_operator
{
	OP_REDIR_RIGHT2,
	OP_REDIR_LEFT2,
	OP_AND,
	OP_OR,
	OP_PIPE,
	OP_REDIR_RIGHT,
	OP_REDIR_LEFT,
	OP_SEMICOLON,
	OP_WORD
};

typedef struct		s_word
{
	char			*word;
	int				type;
	struct s_word	*next;
}					t_word;

void		open_check(char *path);
int			ft_error(int error_num, char *name, int program_end);

/*
**	lexer.c
*/

t_word		*ft_lexer(char *line);

#endif /* !SH_H */
