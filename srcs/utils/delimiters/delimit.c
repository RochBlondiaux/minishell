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
			break;
	}
	i += 2;
	if (input[i] == ' ')
		i ++;
	while (input[i + j] != ' ' && input[i + j])
		j ++;
	return (ft_substr(input, i, i + j));
}

void	delimit_all(t_app *app, char *delimitor)
{
	char	*input;

	input = readline(get_right_prompt(app));
	if (ft_strcmp(input, delimitor) == 0)
		delimit_all(app, delimitor);
	else
		return;
}
