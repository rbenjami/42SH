/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 17:12:44 by smakroum          #+#    #+#             */
/*   Updated: 2014/03/14 16:00:05 by mgarcin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H
# include <libft.h>
# include <fcntl.h>

# define OPEN_REDIR_R O_WRONLY | O_CREAT | O_TRUNC
# define OPEN_2REDIR_R O_WRONLY | O_CREAT | O_APPEND

enum				e_token
{
	STRING,
	OPERATOR
};

enum				e_operator
{
	OP_REDIR_R,
	OP_REDIR_L,
	OP_2REDIR_R,
	OP_2REDIR_L,
	OP_PIPE,
	OP_AND,
	OP_OR,
	OP_SEMI_COL,
	OP_BIN_AND
};

typedef struct		s_redir
{
	char			*name;
	int				flag;
}					t_redir;

typedef struct		s_token
{
	char			*value;
	int				type;
	int				prio;
	t_redir			*redir;
	struct s_token	*next;
}					t_token;

typedef struct		s_ast
{
	t_token			*tk;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct		s_find
{
	char			*cmd;
	int				(*f)(char **);
}					t_find;

typedef pid_t (*op_func)(t_ast *tree, int pfd_old[2]);

typedef struct		s_handler
{
	op_func			*tab_op;
	char			**env;
	int				cmd;
}					t_handler;

/*
**	GLOBAL !
*/
t_handler			handler;

int		error(const char *s1, char *s2);

int		is_operator(char c);
int		is_space(char c);
int		is_quote(char c);
int		is_alpha(char c);

void	add_token(t_token **token, char *value, enum e_token);

void	fill_tree(t_token *tk, t_ast **tree);
int		init_tree(t_token *tk, t_ast **tree);

void	lexer(t_token **token, char *line);

void	init_op(op_func *tab_op[]);
int		ft_ind_op(char *v);
void	close_pfd(int pfd[2]);
void	dup_close(int *pfd, int *pfd_old, int b);
pid_t	op_redir_right(t_ast *tree, int pfd_old[2]);
pid_t	op_redir_left(t_ast *tree, int pfd_old[2]);
pid_t	op_double_redir_right(t_ast *tree, int pfd_old[2]);
pid_t	op_double_redir_left(t_ast *tree, int pfd_old[2]);
pid_t	op_pipe(t_ast *tree, int pfd_old[2]);
pid_t	op_and(t_ast *tree, int pfd_old[2]);
pid_t	op_or(t_ast *tree, int pfd_old[2]);
pid_t	op_semi_col(t_ast *tree, int pfd_old[2]);
pid_t	op_bin_and(t_ast *tree, int pfd_old[2]);

pid_t	execute(char *cmd, int	pfd_old[2], int	pfd[2], int b);

void	resolve_tree(t_ast *tree, int pfd_old[2]);

void	parse_string(t_token **token);

char	*ft_getenv(const char *name);

int		(*find_builtin(char *cmd))(char **);

/*
**	BUILTIN
*/
int		builtin_echo(char **argv);
int		builtin_cd(char **av);
int		builtin_exit(char **av);
int		builtin_env(char **av);
int		builtin_setenv(char **av);
int		builtin_unsetenv(char **av);

#endif /* !SH_H */
