/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 17:02:54 by tdeniset          #+#    #+#             */
/*   Updated: 2014/02/27 22:10:22 by mgarcin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include <stdio.h> // A VIRER

int				main(int ac, char **av)
{
	t_controle	controle;

	if (ac > 1)
	{
		controle.start = NULL;
		controle.f_spe_c[0] = ft_lexer_bkslash;
		controle.f_spe_c[1] = ft_lexer_space;
		controle.f_spe_c[2] = ft_lexer_quote;
		ft_lexer(av[1], 0, &controle);
	}
	return (0);
}

char			*ft_lexer(char *str, int i, t_controle *controle)
{
	int		ret;

	if ((ret = ft_is_spe_c(str[i])))
		return ((*controle->f_spe_c[ret - 1])(str, i, controle));
	if (str[i] != '\0')
	{
		add_char(str[i]);
		str = ft_lexer(str, i + 1, controle);
	}
	return (str);
}

char			*ft_lexer_bkslash(char *str, int i, t_controle *controle)
{
	if (str[i + 1] == '\0')
	{
		;//str = ft_read_more(str + i);
	}
	add_char(str[i + 1]);
	ft_lexer(str, i + 2, controle);
	return (str + 1);
}

char			*ft_lexer_space(char *str, int i, t_controle *controle)
{
	add_char('\n');
	ft_lexer(str, i + 1, controle);
	return (str);
}

char			*ft_lexer_quote(char *str, int i, t_controle *controle)
{
	add_char('\"');
	while (str[i] && str[i] != '\"')
		i++;
	ft_lexer(str, i + 1, controle);
	return (str);
}

enum e_spe_c	ft_is_spe_c(char c)
{
	if (c == '\\')
		return (BK_SLASH);
	else if (c == ' '|| c == '\t')
		return (SPACE);
	else if (c == '"')
		return (QUOTE);
	else
		return (0);
}

/*char	*ft_read_more(char *s)
{
	char	buff[BUFF_SIZE + 1];
	int		ret;
	char	*tmp;

	s = (s == NULL) ? ft_strnew(0) : s;
	while ((ret = read(0, buff, BUFF_SIZE)))
	{
		buff[ret] = '\0';
		tmp = s;
		s = ft_strjoin(s, buff);
		ft_strdel(tmp);
	}
	return (s);
}
*/
void		add_token(t_controle *controle, char *value, enum e_spe_c type)
{
	t_token	*tmp;
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token)
	{
		new_token->value = value;
		new_token->type = type;
		new_token->next = NULL;
	}
	if (!controle->start)
		controle->start = new_token;
	else
	{
		tmp = controle->start;
		while ((controle->start)->next)
			controle->start = (controle->start)->next;
		(controle->start)->next = new_token;
		controle->start = tmp;
	}
}

t_token		*get_last_token(t_controle *controle)
{
	t_token	*tmp;

	tmp = controle->start;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void			add_char(char c)
{
	write(1, &c, 1);
}
