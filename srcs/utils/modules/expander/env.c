/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/04 10:22:45 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static int	should_ignore(char *i, size_t start, size_t end)
{
	int		q;
	size_t	index;

	q = 0;
	index = -1;
	if (index - start == 1)
		return (TRUE);
	while (i[++index] && index <= end)
	{
		is_in_quotes(&q, i[index]);
		if (index == start)
			return (q == 2);
	}
	return (FALSE);
}

static char	*get_remaining(char *i, int *i1)
{
	size_t	start;
	size_t	index;

	start = ft_strchr(&i[*i1], '$');
	if (start > 0)
		start += *i1;
	if (start == 0 || i[start + 1] == '?')
	{
		(*i1)++;
		return (NULL);
	}
	index = start;
	while (i[++index] && ft_isalnum(i[index]))
		;
	if (should_ignore(i, start, index))
	{
		(*i1) += ft_strchr(&i[start], '$') + 1;
		return (NULL);
	}
	(*i1) += (index - start);
	return (ft_substr(i, start, index - start));
}

char	*expand_env_vars(t_app *app, char *input)
{
	char	*t;
	char	*key;
	char	*value;
	int		index;

	index = 0;
	t = ft_strdup(input);
	key = get_remaining(t, &index);
	while (t[index])
	{
		if (key)
		{
			value = get_env(app, &key[1]);
			if (!value)
				value = "";
			reset_str(&t, replace_first(t, key, value));
			free(key);
		}
		key = get_remaining(t, &index);
	}
	free(key);
	return (t);
}
