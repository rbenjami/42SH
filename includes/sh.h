/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 13:28:19 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/02 17:16:44 by dsousa           ###   ########.fr       */
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

// enum	e_token
// {
// 	STRING,
// 	DIGIT,
// 	ALPHA,
// 	OPERATOR,
// 	QUOTE
// };

enum	e_token
{
	STRING,
	OPERATOR
};

typedef struct		s_token
{
	char			*value;
	enum e_token	type;
	struct s_token	*next;
}					t_token;

typedef struct 		s_ast
{
	t_token			*tk;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct		s_ctrl
{
	t_ast			*ast_start;
	t_token			*tk_start;
	char			**env;
}					t_ctrl;

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

#endif /* !SH_H */
