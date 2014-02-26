/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 15:09:37 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/26 16:53:35 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

//	ls -a|cat Makefile -e > pok|wc;ls
//	ls -a|cat > pok -e|wc;ls

enum	e_operator
{
	OP_PIPE,
	OP_REDIR_RIGHT,
	OP_REDIR_LEFT,
	OP_REDIR_RIGHT2,
	OP_REDIR_LEFT2,
	OP_SEMICOLON,
	OP_AND,
	OP_OR,
	OP_FILE,
	OP_CMD
};

typedef struct		s_word
{
	char			*word;
	int				type;
	struct s_word	*next;
}					t_word;

void		ft_word_add(t_word **word, char *str, int type)
{
	t_word	*tmp;
	t_word	*new_word;

	new_word = (t_word *)malloc(sizeof(t_word));
	if (!*word)
		*word = new_word;
	else
	{
		tmp = *word;
		while ((*word)->next)
			*word = (*word)->next;
		(*word)->next = new_word;
		*word = tmp;
	}
}

int			ft_find_op(char *str, int i)
{
	if (str[i] == '|')
		return (OP_PIPE);
	if (str[i] == '>')
		return (OP_REDIR_RIGHT);
	return (-1);
}

t_word		*ft_lexer(char *line)
{
	int		i;
	int		type;
	t_word	*word;
	int		check_bs;
	int		save;
	char	c;

	word = NULL;
	i = 0;
	save = 0;
	while (line[i] != '\0')
	{
		check_bs = 0;
		while (line[i++] == '\\')
			check_bs = !check_bs;
		type = ft_find_op(line, i);
		if (type > 0)
		{
			ls|wc
			ft_word_add(&word, ft_strsub(line, save, i - 1 - save), OP_CMD);
			c = line[i];
			ft_word_add(&word, &ßc, type);
			save = i;
		}
		i++;
	}
	return (word);
}
