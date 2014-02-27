/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 15:09:37 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/27 12:04:21 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

//	ls -a|cat Makefile -e > pok|wc;ls
//	ls -a|cat > pok -e|wc;ls

int		ft_word_add(t_word **word, char *str, int type)
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
	return (ft_strlen(str));
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

char	*ft_detect_word(char *line, int i)
{
	int		save;

	save = i;
	while (line[i] == ' ')
		i++;
	while (line[i] != ' ')
		i++;
	return (ft_strsub(line, save, i - save));
}

t_word		*ft_lexer(char *line)
{
	int		i;
	int		type;
	t_word	*word;
	int		save;
	int		index;

	word = NULL;
	i = 0;
	save = 0;
	while (line[i] != '\0')
	{
		save = 0;
		type = ft_find_op(line, &i);
		write(1, &line[i], 1);
		if (line[i + 1])
			write(1, &line[i + 1], 1);
		if (type >= 0)
		{
			index = (type <= 3) ? 1 : 0;
			ft_word_add(&word, "", OP_WORD);
			ft_word_add(&word, ft_strsub(line, i, 1 + index), type);
			i += (1 + index);
		}
		else
			i += ft_word_add(&word, ft_detect_word(line, i), OP_WORD);
		while (line[i] == ' ')
			i++;
	}
	return (word);
}
