/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 15:09:37 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/26 18:35:05 by rbenjami         ###   ########.fr       */
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
		new_word->word = str;
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

int			ft_find_op(char *str, int *i)
{
	if (str[*i] == '>' && str[*i + 1] == '>')
		return (OP_REDIR_RIGHT2);
	if (str[*i] == '<' && str[*i + 1] == '<')
		return (OP_REDIR_LEFT2);
	if (str[*i] == '&' && str[*i + 1] == '&')
		return (OP_AND);
	if (str[*i] == '|' && str[*i + 1] == '|')
		return (OP_OR);
	if (str[*i] == '|')
		return (OP_PIPE);
	if (str[*i] == '>')
		return (OP_REDIR_RIGHT);
	if (str[*i] == '<')
		return (OP_REDIR_LEFT);
	if (str[*i] == ';')
		return (OP_SEMICOLON);
	return (-1);
}

t_word		*ft_lexer(char *line)
{
	int		i;
	int		type;
	t_word	*word;
	int		check_bs;
	int		save;
	int		index;

	word = NULL;
	i = 0;
	save = 0;
	while (line[i] != '\0')
	{
		check_bs = 0;
		while (line[i] == '\\')
		{
			check_bs = !check_bs;
			i++;
		}
		type = ft_find_op(line, &i);
		if (type >= 0)
		{
			index = (type <= 3) ? 1 : 0;
			if (index)
				i++;
			ft_word_add(&word, ft_strsub(line, save, i - index), OP_WORD);
			ft_word_add(&word, ft_strsub(line, i, 1), type);
			save = i + 1;
		}
		else if (line[i + 1] == '\0')
			ft_word_add(&word, ft_strsub(line, save, i + 1), OP_WORD);
		i++;
	}
	return (word);
}
