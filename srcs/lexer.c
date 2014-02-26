/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 15:09:37 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/26 17:10:23 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

//	ls -a|cat Makefile -e > pok|wc;ls
//	ls -a|cat > pok -e|wc;ls

void		ft_word_add(t_word **word, char *str, int type)
{
	t_word	*tmp;
	t_word	*new_word;

	new_word = (t_word *)malloc(sizeof(t_word));
	if (new_word)
	{
		new_word->word = ft_strdup(str);
		new_word->type = type;
		new_word->next = NULL;
	}
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
		if (type > 0 || line[i + 1] == '\0')
		{
			ft_word_add(&word, ft_strsub(line, save, i), OP_CMD);
			c = line[i];
			ft_word_add(&word, &c, type);
			save = i;
		}
		i++;
	}
	ft_putendl(word->word);
	return (word);
}
