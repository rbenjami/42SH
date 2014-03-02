/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 17:04:33 by tdeniset          #+#    #+#             */
/*   Updated: 2014/02/27 22:10:23 by mgarcin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A42SH_H
# define A42SH_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_controle	t_controle;

enum	e_spe_c
{
	COMMON,
	BK_SLASH,
	SPACE,
	OP_REDIR_RIGHT2,
	OP_REDIR_LEFT2,
	OP_AND,
	OP_OR,
	OP_PIPE,
	OP_REDIR_RIGHT,
	OP_REDIR_LEFT,
	OP_SEMICOLON,
	QUOTE
};

typedef struct		s_token
{
	char			*value;
	enum e_spe_c	type;
	struct s_token	*next;
}					t_token;

struct		s_controle
{
	t_token	*start;
	char	*(*f_spe_c[QUOTE])(char *, int, t_controle *);
};

char			*ft_lexer(char *, int, t_controle *);
char			*ft_lexer_bkslash(char *, int, t_controle *);
char			*ft_lexer_space(char *, int, t_controle *);
char			*ft_lexer_quote(char *, int, t_controle *);

enum e_spe_c	ft_is_spe_c(char);
void			add_token(t_controle *, char *, enum e_spe_c);
t_token			*get_last_token(t_controle *);
void			add_char(char);

#endif
