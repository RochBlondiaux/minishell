/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:36:33 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/26 16:46:21 by rblondia         ###   ########.fr       */
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

static size_t	get_commands_count(char **args)
{
	size_t	index;
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

static t_command	**complementary_parse(t_command **commands)
{
	size_t	index;

	index = 0;
	while (commands[++index])
		parse_redirections(commands[index]);
	return (commands);
}

t_command	**parse(char **args)
{
	int			index;
	size_t		cmds;
	t_command	**commands;

	commands = malloc(sizeof(t_command *) * (get_commands_count(args) + 1));
	if (!commands)
		return (NULL);
	index = 0;
	cmds = -1;
	while (args[index])
	{
		commands[++cmds] = create_command(args, args[index], &index);
		if (is_separator(args[index]))
		{
			// TODO : parse separator
		}
		if (index >= (int) array_length(args))
			break ;
		index++;
	}
	commands[++cmds] = NULL;
	free_array(args);
	return (complementary_parse(commands));
}
