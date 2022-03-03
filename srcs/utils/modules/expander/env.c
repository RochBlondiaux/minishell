/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
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
	while (i[++index] && index < end)
	{
		is_in_quotes(&q, i[index]);
		if (index == start)
			return (q == 2);
	}
	return (FALSE);
}

static char	*get_remaining(char *i)
{
	size_t	start;
	size_t	index;

	start = ft_strchr(i, '$');
	if (start == 0 || i[start + 1] == '?' || !i[start + 1])
		return (NULL);
	index = start;
	while (i[++index] && ft_isalnum(i[index]))
		;
	if (should_ignore(i, start, index))
		return (NULL);
	return (ft_substr(i, start, index - start));
}

void	expand_env_vars(t_app *app, char **input)
{
	char	*t;
	char	*key;
	char	*value;
	int		index;

	index = -1;
	t = ft_strdup(*input);
	key = get_remaining(t);
	while (input[++index])
	{
		if (key)
		{
			value = get_env(app, &key[1]);
			if (!value)
				value = "";
			reset_str(&t, replace_str(t, key, value));
			index += ft_strlen(value);
			free(key);
		}
		key = get_remaining(t);
	}
	free(key);
	*input = t;
}
