/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 13:28:19 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/28 17:48:41 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H
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

enum	e_token
{
	STRING,
	DIGIT,
	ALPHA,
	OPERATOR,
	QUOTE
};

typedef struct			s_token
{
	char				*value;
	enum e_token		type;
	struct s_token		*next;
}						t_token;

typedef struct			s_hist
{
	char				*data;
	struct s_hist		*next;
	struct s_hist		*prev;
	struct s_hist		*start;
	struct s_hist		*last;
	int					new;
}						t_hist;

void		open_check(char *path);
int			ft_error(int error_num, char *name, int program_end);

/*
**	lexer.c
*/
void		lexer(t_token **token, char *line);

/*
**	lexer_is.c
*/
int			is_operator(char c);
int			is_space(char c);
int			is_quote(char c);
int			is_alpha(char c);

/*
**	token.c
*/
void		add_token(t_token **token, char *value, enum e_token type);

/*
**	operator.c
*/
int			find_op(char *str);

/*
**	getenv.c
*/
char		*ft_getenv(const char *name);

/*
**	histfile.c
*/
void		creat_hist(t_hist *hist);
void		save_hist(t_hist *hist, char *line, int new);

/*
** history.c
*/
void	builtin_history_c(t_hist *start);
void	builtin_history(t_hist *hist);

#endif /* !SH_H */
