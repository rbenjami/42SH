/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: killer <killer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 17:12:44 by smakroum          #+#    #+#             */
/*   Updated: 2014/03/22 18:25:30 by killer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H
# include <libft.h>
# include <fcntl.h>
# include <stdarg.h>
# include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

# define OPEN_REDIR_R O_WRONLY | O_CREAT | O_TRUNC
# define OPEN_2REDIR_R O_WRONLY | O_CREAT | O_APPEND
# define UP 4283163
# define LEFT 4479771
# define RIGHT 4414235
# define DOWN 4348699
# define SUPR 2117294875
# define DEL 127

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
	struct s_redir	*next;
}					t_redir;

typedef struct		s_token
{
	char			*value;
	int				type;
	int				prio;
	t_redir			*redir;
	struct s_token	*prev;
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
	int (*f)(char **);
}					t_find;

typedef pid_t (*op_func)(t_ast *tree, int pfd_old[2]);

typedef struct		s_handler
{
	op_func			*tab_op;
	char			**env;
	int				cmd;
}					t_handler;

typedef struct		s_exe
{
	char			**args;
	char			*path;
	pid_t			pid;
	int				ret;
	int				(*builtin)(char **);
}					t_exe;

typedef struct			s_line
{
	char				data;
	struct s_line		*next;
	struct s_line		*prev;
	int					nb;
}						t_line;

typedef struct			s_key
{
	int					key;
	void				(*f)(char *, int *, t_line *);
}						t_key;

/*
**	GLOBAL !
*/
t_handler			handler;

int		error(const char *msg, ...)
						__attribute__((format(printf, 1, 2)));

int		is_operator(char c);
int		is_space(char c);
int		is_quote(char c);
int		is_alpha(char c);

void	add_token(t_token **token, char *value, enum e_token);
void	free_token(t_token **token);
t_token	*append_token(t_token **token, t_token **add);

void	fill_tree(t_token *tk, t_ast **tree);
int		init_tree(t_token *tk, t_ast **tree);

void	lexer(t_token **token, char *line);

void	init_op(op_func *tab_op[]);
int		ft_ind_op(char *v);

pid_t	op_redir(t_ast *tree, int pfd_old[2]);

pid_t	op_redir(t_ast *tree, int pfd_old[2]);
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
void	ft_modify_token_for_redir(t_token **token);
void	prompt(void);

/*
**	utils.c
*/
void	close_pfd(int pfd[2]);
void	dup_close(int *pfd, int *pfd_old, int b);
int		ft_isfuncfork(char *name);
char	**default_env(void);

/*
**	BUILTIN
*/
int		builtin_echo(char **argv);
int		builtin_cd(char **av);
int		builtin_exit(char **av);
int		builtin_env(char **av);
int		builtin_setenv(char **av);
int		builtin_unsetenv(char **av);

/*
**	reader.c
*/
char		*reader(int fd);
char		*create_line(t_line *list);

/*
**	cmp_key.c
*/
int			cmp_key(char *key, int *cursor, t_line *list);
void		delete_first(t_line *list);
void		print_rest(int cursor, t_line *list);

/*
**	tputs_putchar.c
*/
int			tputs_putchar(int c);


/*
**	list_termcap.c
*/
void		modif_list(t_line *list, char *c, int *cursor);

/*
**	tools_term.c
*/
int			ft_match(char *c, char search);
t_line		*obtain_list(int cursor, t_line *list);
void		verif_nb(t_line *list);
int			list_len(t_line *list);
int			len_prompt(void);

/*
**	exec_key.c
*/
void		ft_left(char *key, int *cursor, t_line *list);
void		ft_right(char *key, int *cursor, t_line *list);
void		ft_del(char *key, int *cursor, t_line *list);
void		ft_supr(char *key, int *cursor, t_line *list);

#endif /* !SH_H */
