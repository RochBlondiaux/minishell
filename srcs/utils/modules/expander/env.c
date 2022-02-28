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

char	*get_env_string(char *input, int *index)
{
	size_t	end;
	char	*key;

	end = ft_strchr(&input[*index], ' ');
	if (end == 0)
		end = ft_strlen(input);
	key = ft_substr(input, *index, end);
	if (!key)
		return (NULL);
	*index += end;
	return (key);
}

char	*get_next_env_vars(char *input, int *index)
{
	size_t	i;

	i = *index;
	while (input[++i])
	{
		if (input[i] != '$' || !input[i + 1] || !ft_isalnum(input[i + 1]))
			continue ;
		*index = i;
		return (get_env_string(input, index));
	}
	*index = i;
	return (NULL);
}

void	expand_env_vars(t_app *app, char **input)
{
	int		i;
	char	*key;
	char	*value;
	char	*r;

	i = -1;
	r = *input;
	while (i < (int) ft_strlen(r))
	{
		key = get_next_env_vars(r, &i);
		if (key)
		{
			value = get_env(app, &key[1]);
			if (!value)
			{
				free(key);
				continue ;
			}
			r = replace_str(r, key, value);
			free(key);
		}
	}
	*input = r;
}
