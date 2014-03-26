/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 13:48:37 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/26 16:25:36 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	sup_quote(char **token)
{
	int		i[5] = {0, 0, 0, 0, 0};

	while ((*token)[i[0]] != '\0')
	{
		if ((*token)[i[0]] == BACK_SLASH || i[1])
		{
			if ((*token)[i[0]] == BACK_SLASH)
				i[0]++;
			i[1] = !i[1];
		}
		if ((*token)[i[0]] == DOUBLE_QUOTE)
			i[2] = (i[3]) ? i[2] : !i[2];
		if ((*token)[i[0]] == QUOTE)
			i[3] = (i[2]) ? i[3] : !i[3];
		if (!is_quote((*token)[i[0]])
		|| ((*token)[i[0]] == DOUBLE_QUOTE && i[3])
		|| ((*token)[i[0]] == QUOTE && i[2]) || i[1])
			(*token)[i[4]++] = (*token)[i[0]];
		i[0]++;
	}
	while ((*token)[i[4]] != '\0')
		(*token)[i[4]++] = '\0';
}

void	missing_quote(int dquote, t_token *token)
{
	char	*line;

	if (dquote)
		ft_putstr("\033[31mdquote>\033[m ");
	else
		ft_putstr("\033[31mquote>\033[m ");
	line = reader(IN, handler.hist);
	ft_strjoin2(&token->value, "\n");
	ft_strjoin2(&token->value, line);
	free(line);
	parse_string(&token);
}

void	parse(t_token *token)
{
	int		i;
	int		dquote;
	int		quote;

	i = 0;
	dquote = 0;
	quote = 0;
	while (token->value[i] != '\0')
	{
		if (token->value[i] == BACK_SLASH)
			i++;
		else
		{
			if (token->value[i] == DOUBLE_QUOTE)
				dquote = (quote) ? dquote : !dquote;
			if (token->value[i] == QUOTE)
				quote = (dquote) ? quote : !quote;
		}
		i++;
	}
	if (dquote || quote)
		missing_quote(dquote, token);
	else
		sup_quote(&token->value);
}

int		ft_strchr_redir(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' || str[i] == '<')
			j++;
		else if (j == 1 || j == 2)
			break ;
		i++;
	}
	if (j == 1 || j == 2)
		return (1);
	return (0);
}

void	parse_string(t_token **token)
{
	t_token		*tmp;

	tmp = (*token);
	while (tmp)
	{
		if (tmp->type == STRING)
			parse(tmp);
		tmp = tmp->next;
	}
}
