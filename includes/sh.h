/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 13:28:19 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/03 20:09:30 by mgarcin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H
# include <libft.h>

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


int		is_operator(char c);
int		is_space(char c);
int		is_quote(char c);
int		is_alpha(char c);

void	add_token(t_token **token, char *value, enum e_token);

int		fill_tree(t_token *tk, t_ast **tree);
int		init_tree(t_token *tk, t_ast **tree);

#endif /* !SH_H */
