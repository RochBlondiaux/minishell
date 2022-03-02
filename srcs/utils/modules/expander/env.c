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

static int	get_end(char *input, char i, int *q)
{
	size_t	index;

	index = i;
	while (input[index])
	{
		if (*q == 0)
		{
			if (input[index] == ' ' || input[index] == '$')
				return (index);
		}
		else if (*q == 1)
		{
			if (input[index] == '\'')
			{
				*q = 0;
				return (index);
			}
		}
		else if (*q == 2)
		{
			if (input[index] == '"')
			{
				*q = 0;
				return (index);
			}
		}
		index++;
	}
	return (index);
}

static char	*get_env_string(char *input, int *index, int * q)
{
	size_t	end;
	char	*key;

	if (*q == 0)
		end = ft_strchr(&input[*index], ' ');
	else if (*q == 1)
		end = ft_strchr(&input[*index], '\'');
	else if (*q == 2)
		end = ft_strchr(&input[*index], '"');
	if (end == 0)
		end = get_end(input, *index, q);
	key = ft_substr(input, *index, end);
	if (!key)
		return (NULL);
	if (end == 0)
		end++;
	*index += end - 1;
	return (key);
}

static char	*get_next_env_vars(char *input, int *index, int *q)
{
	size_t	i;

	i = *index;
	while (input[++i])
	{
		if (input[i] == '\'')
			*q = 1;
		if (input[i] == '"')
			*q = 2;
		if (input[i] != '$' || !input[i + 1] || !ft_isalnum(input[i + 1]))
			continue ;
		*index = i;
		return (get_env_string(input, index, q));
	}
	*index = i;
	return (NULL);
}

void	expand_env_vars(t_app *app, char **input)
{
	int		i;
	char	*t;
	char	*key;
	char	*value;
	int		q;

	i = -1;
	q = 0;
	t = ft_strdup(*input);
	while (t[++i])
	{
		key = get_next_env_vars(t, &i, &q);
		if (key)
		{
			if (q != 1)
				value = get_env(app, &key[1]);
			else if (q == 1)
				value = ft_strdup(key);
			if (!value)
				value = ft_strdup("");
			if (q != 1)
				reset_str(&t, replace_str(t, key, value));
			else
				free(value);
			free(key);
		}
	}
	*input = t;
}
