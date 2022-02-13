/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static size_t	get_args_count(char **args)
{
	size_t	i;
	size_t	j;
	size_t	c;
	int		quotes;

	i = -1;
	c = 0;
	quotes = 0;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
			is_in_quotes(&quotes, args[i][j]);
		if (quotes == 0)
			c++;
	}
	return (c);
}

static void	fill_args(char *raw, char **new)
{
	size_t	i;
	int		q;
	size_t	start;
	size_t	n;

	i = -1;
	q = 0;
	start = 0;
	n = 0;
	while (raw[++i])
	{
		if ((q == '\'' && raw[i] == q)
			|| (q == '"' && raw[i] == q)
			|| (q == 0 && raw[i] == ' '))
		{
			if (i - start == 0)
				continue ;
			q = 0;
			new[n++] = ft_substr(raw, start, i - start);
			start = i + 1;
			continue ;
		}
		if ((raw[i] == '\'' || raw[i] == '"' || raw[i] == ' ') && q == 0)
		{
			start = i + 1;
			if (raw[i] != ' ')
				q = raw[i];
		}
	}
	if (start <= ft_strlen(raw))
		new[n++] = ft_substr(raw, start, ft_strlen(raw) - start);
	new[n++] = NULL;
}

static void	trim_args(char **args)
{
	size_t	i;

	i = -1;
	while (args[++i])
		args[i] = ft_strtrim(args[i], " ");
}

char	**parse_quotes(char *raw)
{
	char	**args;
	char	**new;

	args = ft_split(raw, ' ');
	new = malloc(sizeof (char *) * (get_args_count(args) + 1));
	if (!new)
	{
		free_array(args);
		return (NULL);
	}
	fill_args(raw, new);
	trim_args(new);
	free_array(args);
	return (new);
}
