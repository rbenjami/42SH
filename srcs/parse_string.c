/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 13:48:37 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/11 13:03:26 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_strjoin2(char **str1, char *str2)
{
	char	*tmp;

	tmp = ft_strjoin(*str1, str2);
	ft_strdel(&(*str1));
	*str1 = ft_strdup(tmp);
	ft_strdel(&tmp);
}

void	parse(t_token *token)
{
	char	*line;
	int		i;
	int		dquote;
	int		quote;

	i = 0;
	dquote = 0;
	quote = 0;
	while (token->value[i] != '\0')
	{
		if (token->value[i] == BACK_SLASH)
			i += 2;
		if (token->value[i] == DOUBLE_QUOTE)
			dquote = (quote) ? dquote : !dquote;
		if (token->value[i] == QUOTE)
			quote = (dquote) ? quote : !quote;
		i++;
	}
	if (dquote || quote)
	{
		if (dquote)
			ft_putstr("\033[31mdquote>\033[m ");
		else
			ft_putstr("\033[31mquote>\033[m ");
		get_next_line(IN, &line);
		ft_strjoin2(&token->value, "\n");
		ft_strjoin2(&token->value, line);
		free(line);
		parse_string(&token);
	}
}

void	sup_quote(char **token)
{
	int		i;
	int		cpy;
	int		dquote;
	int		quote;
	int		back;

	i = 0;
	cpy = 0;
	dquote = 0;
	quote = 0;
	back = 0;
	while ((*token)[cpy] != '\0')
	{
		if ((*token)[cpy] == BACK_SLASH || back)
		{
			cpy++;
			back = !back;
		}
		if ((*token)[cpy] == DOUBLE_QUOTE)
			dquote = (quote) ? dquote : !dquote;
		if ((*token)[cpy] == QUOTE)
			quote = (dquote) ? quote : !quote;
		if (!is_quote((*token)[cpy])
		|| ((*token)[cpy] == DOUBLE_QUOTE && quote)
		|| ((*token)[cpy] == QUOTE && dquote) || back)
			(*token)[i++] = (*token)[cpy];
		cpy++;
	}
	while ((*token)[i] != '\0')
		(*token)[i++] = '\0';
}

void	parse_string(t_token **token)
{
	t_token		*tmp;

	tmp = (*token);
	while (tmp)
	{
		if (tmp->type == STRING)
		{
			parse(tmp);
			sup_quote(&tmp->value);
		}
		tmp = tmp->next;
	}
}
