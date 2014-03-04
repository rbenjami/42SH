/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 16:00:07 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/04 17:51:59 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			collect_string(t_token **token, char *line)
{
	int		i;
	char	*str;
	int		quote;
	char	q;

	i = 0;
	quote = 0;
	q = 0;
	while (line[i] && (!is_operator(line[i]) || quote))
	{
		if (line[i] == '\\')
			i++;
		if (is_quote(line[i]) && (line[i] == q || q == 0))
		{
			q = line[i];
			quote = !quote;
		}
		i++;
	}
	str = ft_strsub(line, 0, i);
	add_token(token, str, STRING);
	ft_strdel(&str);
	return (i - 1);
}

int			collect_operator(t_token **token, char *line)
{
	int		i;
	char	*str;

	i = 0;
	while (is_operator(line[i]))
		i++;
	str = ft_strsub(line, 0, i);
	add_token(token, str, OPERATOR);
	ft_strdel(&str);
	return (i - 1);
}
void		lexer(t_token **token, char *line)
{
	int		i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (line[i] == '\\')
		i++;
	else if (is_operator(line[i]))
		i += collect_operator(token, &line[i]);
	else if (line[i] != '\0')
		i += collect_string(token, &line[i]);
	if (line[i] != '\0' && line[i + 1] != '\0')
		lexer(token, &line[++i]);
}

///////////////////	DEBUG !

char* tab_type[2] =
{
	"STRING",
	"OPERATOR"
};

void	DEBUG(t_token *token)
{
	while (token)
	{
		ft_putstr("\033[32mTYPE: \033[33m");
		ft_putstr(tab_type[token->type]);
		ft_putstr("\033[m : \033[31m");
		ft_putnbr(token->type);
		ft_putstr("\n\033[32mVALUE: \033[33m");
		ft_putendl(token->value);
		ft_putstr("\033[32mPRIORITY: \033[33m");
		ft_putnbr(token->prio);
		ft_putstr("\n\n\033[0m");
		token = token->next;
	}
}

void	DEBUG2(t_ast *tree)
{
	if (tree)
	{
		ft_putstr("\033[32mTYPE: \033[33m");
		ft_putstr(tab_type[tree->tk->type]);
		ft_putstr("\033[m : \033[31m");
		ft_putnbr(tree->tk->type);
		ft_putstr("\n\033[32mVALUE: \033[33m");
		ft_putendl(tree->tk->value);
		ft_putstr("\033[32mPRIORITY: \033[33m");
		ft_putnbr(tree->tk->prio);
		ft_putstr("\n\n\033[0m");
		DEBUG2(tree->left);
		DEBUG2(tree->right);
	}
}
///////////////////	DEBUG !

void	free_token(t_token **token)
{
	t_token		*tmp;

	while (*token)
	{
		tmp = *token;
		*token = (*token)->next;
		free(tmp->value);
		tmp->value = NULL;
		//ft_strdel(&tmp->value);
		free(tmp);
		tmp = NULL;
	}
		//ft_memdel((void **)&tmp);
}

void	free_ast(t_ast **tree)
{
	if (*tree)
	{
		free_ast(&(*tree)->left);
		free_ast(&(*tree)->right);
	//	ft_putstr("delete : ");
	//	ft_putendl((*tree)->tk->value);
		free((*tree)->tk->value);
		(*tree)->tk->value = NULL;
		free((*tree)->tk);
		(*tree)->tk = NULL;
		free(*tree);
		*tree = NULL;
	}
}

int		main(void)
{
	char		*line;
	t_token		*token;
	t_ast		*tree;

	token = NULL;
	tree = NULL;
	while (1)
	{
		ft_putstr("~> ");
		if (get_next_line(0, &line) <= 0)
			exit(0);
		// execute(line);
		lexer(&token, line);
		free(line);
		fill_tree(token, &tree);
		resolve_tree(tree);
		// DEBUG2(tree);
		free_ast(&tree);
		token = NULL;
	}
	return (0);
}
