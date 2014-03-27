/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_sh.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 19:36:30 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/27 16:22:46 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// lignes 48, ligne 51, ligne 86
#ifndef STRUCT_SH_H
# define STRUCT_SH_H

typedef struct winsize	t_ws;

typedef struct			s_redir
{
	char				*name;
	int					flag;
	struct s_redir		*next;
}						t_redir;

typedef struct			s_token
{
	char				*value;
	int					type;
	int					prio;
	t_redir				*redir;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

typedef struct			s_ast
{
	t_token				*tk;
	struct s_ast		*left;
	struct s_ast		*right;
}						t_ast;

typedef int				(*t_f)(char **);

typedef struct			s_find
{
	char				*cmd;
	t_f					find;
}						t_find;

typedef pid_t			(*t_op_func)(t_ast *tree, int pfd_old[2]);
typedef int				(*t_buil)(char **);

typedef struct			s_hist
{
	char				*data;
	struct s_hist		*next;
	struct s_hist		*prev;
	int					new;
}						t_hist;

typedef struct			s_ctrl_h
{
	struct s_hist		*start;
	struct s_hist		*last;
	int					nb;
	int					unused;
}						t_ctrl_h;

typedef struct			s_handler
{
	t_op_func			*tab_op;
	char				**env;
	int					cmd;
	int					len;
	struct termios		*term;
	t_ctrl_h			*hist;
}						t_handler;

typedef struct			s_exe
{
	char				**args;
	char				*path;
	pid_t				pid;
	int					ret;
	t_buil				builtin;
}						t_exe;

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
	void				(*f)(char *, int *, t_line *, t_ctrl_h *);
}						t_key;

#endif /* !STRUCT_SH_H */
