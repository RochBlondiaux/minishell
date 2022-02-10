/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_separator(char *a)
{
	return (ft_strcmp(a, "&&")
		|| ft_strcmp(a, "||")
		|| ft_strcmp(a, "|")
		|| ft_strcmp(a, "&"));
}

static size_t	get_cmds_count(char **args)
{
	int		index;
	size_t	cmds;

	index = -1;
	cmds = 0;
	while (args[++index])
	{
		if (is_separator(args[index]))
			cmds ++;
	}
	return (cmds + 1);
}

char	**parse(char *input)
{
	size_t		len_bloc;
	size_t		i;
	size_t		j;
	size_t		blocs;
	char		**split;
	char		**cmds;
	size_t		size;
	size_t		size_split;

	split = ft_split(input, ' ');
	cmds = malloc(sizeof(char *) * get_cmds_count(split));
	if (!cmds)
		return (NULL);
	i = -1;
	blocs = -1;
	while (split[++i])
	{
		j = i - 1;
		len_bloc = 0;
		while (!is_separator(split[i]) && split[i])
		{
			len_bloc += ft_strlen(split[i]);
			len_bloc ++;
			i ++;
		}
		size = -1;
		cmds[++blocs] = malloc(sizeof(char) * (len_bloc + 1));
		if (!cmds[blocs])
			return (NULL);
		while (++j < i)
		{
			size_split = -1;
			while (split[j][++size_split])
				cmds[blocs][++size] = split[j][size_split];
			cmds[blocs][++size] = ' ';
		}
		cmds[blocs][++size] = '\0';
	if (split[i] != NULL)
		continue;
	else
		break;
	}
	cmds[++blocs] = NULL;
	i = -1;
	while(cmds[++i])
		printf("%s\n", cmds[i]);
	return (cmds);
}
