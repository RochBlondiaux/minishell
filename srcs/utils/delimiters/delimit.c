/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*get_rid_delim(char *input)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
			break ;
	}
	dest = ft_substr(input, 0, i);
	j = 0;
	while (input[i] == ' ' || input[i] == '<')
		i ++;
	while (input[i + j])
	{
		if (input[i + j] == ' ')
			break ;
		j ++;
	}
	dest = ft_strjoin_properly(dest, ft_substr(input, i + j + 1,
				ft_strlen(input) - (i + j + 1)));
	return (dest);
}

int	contains_del(char *input)
{
	size_t	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
			return (1);
	}
	return (0);
}

char	*is_the_del(char *input)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	while (input[++i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
			break ;
	}
	i += 2;
	if (input[i] == ' ')
		i ++;
	while (input[i + j] && input[i + j] != ' ')
		j ++;
	return (ft_substr(input, i, j));
}

char	*delimit_all(t_app *app, char *input, char *delimitor)
{
	char	*line;

	line = readline(DELIMIT_PROMPT);
	if (ft_strcmp_sensitive(line, delimitor) == 0)
		delimit_all(app, input, delimitor);
	return (get_rid_delim(input));
}
