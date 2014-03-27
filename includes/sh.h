/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 17:12:44 by smakroum          #+#    #+#             */
/*   Updated: 2014/03/27 16:22:27 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H
# include <libft.h>
# include <fcntl.h>
# include <stdarg.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include "struct_sh.h"

# define OPEN_REDIR_R O_WRONLY | O_CREAT | O_TRUNC
# define OPEN_2REDIR_R O_WRONLY | O_CREAT | O_APPEND
# define UP 4283163
# define LEFT 4479771
# define RIGHT 4414235
# define DOWN 4348699
# define SUPR 2117294875
# define DEL 127
# define NSF_ERROR "No such file or directory : %s\n"

enum		e_token
{
	STRING,
	OPERATOR
};

enum		e_operator
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

t_handler			g_handler;

int		error(const char *msg, ...);

void	ft_lstremove_redir(t_token **token, t_token **remove);
void	ft_lstadd_redir(t_token *token, char *name, int flag);
int		flag_op(int ind);
int		ft_modify_cmd2(t_token **token, t_token **tmp, int *flag);
int		ft_mod_cmd(t_token **tk, t_token **tmp, t_token **cmd, t_token **redir);

int		is_operator(char c);
int		is_space(char c);
int		is_quote(char c);
int		is_alpha(char c);

void	add_token(t_token **token, char *value, enum e_token t);
void	free_token(t_token **token);
t_token	*append_token(t_token **token, t_token **add);

void	fill_tree(t_token *tk, t_ast **tree);
int		init_tree(t_token *tk, t_ast **tree);

void	lexer(t_token **token, char *line);

void	init_op(t_op_func *tab_op[]);
int		ft_ind_op(char *v);

pid_t	op_redir(t_ast *tree, int pfd_old[2]);

int		redir_read(t_ast *tree, int *fd, int pfd_new[2]);
pid_t	op_redir2(t_ast *t, int pfd_old[2], int pfd[2]);
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

t_buil	find_builtin(char *cmd);
int		ft_modify_token_for_redir(t_token **token);
void	prompt(void);

/*
**	utils.c
*/
void	close_pfd(int pfd[2]);
void	dup_close(int *pfd, int *pfd_old, int b);
int		ft_isfuncfork(char *name);
char	**default_env(void);
void	del_3_str(char **str1, char **str2, char **str3);

/*
**	BUILTIN
*/
int		builtin_echo(char **argv);
int		builtin_cd(char **av);
int		builtin_exit(char **av);
int		builtin_env(char **av);
int		builtin_setenv(char **av);
int		builtin_unsetenv(char **av);
int		builtin_history(char **av);

/*
**	reader.c
*/
char	*reader(int fd, t_ctrl_h *hist);
char	*create_line(t_line *list);
void	freelist(t_line *list);

/*
**	cmp_key.c
*/
int		cmp_key(char *key, int *cursor, t_line *list, t_ctrl_h *h);
void	delete_first(t_line *list);
void	print_rest(int cursor, t_line *list);

/*
**	tputs_putchar.c
*/
int		tputs_putchar(int c);

/*
**	list_termcap.c
*/
void	modif_list(t_line *list, char *c, int *cursor, t_ctrl_h *h);
void	add_list(t_line *list, char *c, int rank, int *cursor);
void	create_list(t_line *list, char *c, int *cursor);
void	add_first(t_line *list, char c, int *cursor);

/*
**	tools_term.c
*/
int		ft_match(char *c, char search);
t_line	*obtain_list(int cursor, t_line *list);
void	verif_nb(t_line *list);
int		list_len(t_line *list);
int		len_prompt(void);

/*
**	exec_key.c
*/
void	ft_left(char *key, int *cursor, t_line *list, t_ctrl_h *h);
void	ft_right(char *key, int *cursor, t_line *list, t_ctrl_h *h);
void	ft_del(char *key, int *cursor, t_line *list, t_ctrl_h *h);
void	ft_supr(char *key, int *cursor, t_line *l, t_ctrl_h *h);

/*
**	histfile.c
*/
void	save_hist(t_hist *hist, char *line, int new, t_ctrl_h *ctrl);
void	create_hist(t_ctrl_h *ctrl);

/*
**	exec_hist.c
*/
void	ft_up(char *key, int *cursor, t_line *list, t_ctrl_h *h);
void	ft_down(char *key, int *cursor, t_line *list, t_ctrl_h *h);

void	turn_on(struct termios *term);
void	turn_off(struct termios *term);

#endif
