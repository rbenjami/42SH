/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 17:12:44 by smakroum          #+#    #+#             */
/*   Updated: 2014/03/05 16:10:51 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H
# include "libft.h"

enum				e_token
{
	STRING,
	OPERATOR
};

typedef struct		s_token
{
	char			*value;
	int				type;
	int				prio;
	struct s_token	*next;
}					t_token;

typedef struct		s_ast
{
	t_token			*tk;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*father;
}					t_ast;

typedef int (*op_func)(t_ast *left, t_ast *rigth);

int		error(const char *s1, char *s2);


int		is_operator(char c);
int		is_space(char c);
int		is_quote(char c);
int		is_alpha(char c);

void	add_token(t_token **token, char *value, enum e_token);

void	fill_tree(t_token *tk, t_ast **tree);
int		init_tree(t_token *tk, t_ast **tree);

void	init_op(op_func *tab_op[]);
int		ft_ind_op(char *v);
int		op_redir_right(t_ast *left, t_ast *right);
int		op_redir_left(t_ast *left, t_ast *right);
int		op_double_redir_right(t_ast *left, t_ast *right);
int		op_double_redir_left(t_ast *left, t_ast *right);
int		op_pipe(t_ast *left, t_ast *right);
int		op_and(t_ast *left, t_ast *right);
int		op_or(t_ast *left, t_ast *right);
int		op_semi_col(t_ast *left, t_ast *right);
int		op_bin_and(t_ast *left, t_ast *right);

pid_t		execute(char *cmd, int	pfd_old[2], int	pfd[2], int b);
// void		execute(char *cmd, int in, int out);

void	resolve_tree(t_ast *tree, int pfd_old[2]);

#endif /* !SH_H */
