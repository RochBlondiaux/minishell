/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:36:33 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:18 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_delimiter_char(char *a)
{
	return (ft_strcmp(a, "<<") || ft_strcmp(a, ">>"));
}


static int	get_arguments(char **args)
{
	size_t	i;
	size_t	count;

	i = -1;
	count = 0;
	while (args[++i])
	{
		if (is_delimiter_char(args[i])
			|| (i > 0 && is_delimiter_char(args[i - 1])))
			continue ;
		count++;
	}
	return (count + 1);
}

static char	**remove_delimiter(char **args)
{
	size_t	i;
	size_t	j;
	char	**a;

	i = -1;
	j = 0;
	a = malloc(sizeof(char *) * get_arguments(args));
	while (args[++i])
	{
		if (is_delimiter_char(args[i])
			|| (i > 0 && is_delimiter_char(args[i - 1])))
			continue ;
		a[j] = ft_strdup(args[i]);
		j++;
	}
	a[j] = NULL;
	free_array(args);
	return (a);
}


void parse_delimiter(t_command *cmd)
{
	size_t	index;
	char	**args;

	index = -1;
	args = cmd->args;
	cmd->delimiter = ft_strdup("");
	cmd->appender = ft_strdup("");
	while (args[++index])
	{
		if (ft_strcmp(args[index], "<<") && args[index + 1])
		{
			free(cmd->delimiter);
			cmd->delimiter = ft_strdup(args[index + 1]);
		}
		else if (ft_strcmp(args[index], ">>") && args[index + 1])
		{
			free(cmd->appender);
			cmd->appender = ft_strdup(args[index + 1]);
		}
	}
	cmd->args = remove_delimiter(args);
}