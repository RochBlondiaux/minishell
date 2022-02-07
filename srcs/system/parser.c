/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:36:33 by rblondia          #+#    #+#             */
/*   Updated: 2022/02/07 14:54:18 by lfilloux         ###   ########.fr       */
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

static t_command	**complementary_parse(t_command **commands)
{
	int	index;

	index = -1;
	while (commands[++index])
	{
		parse_redirections(commands[index]);
		parse_delimiter(commands[index]);
	}
	init_commands(commands);
	return (commands);
}

t_command	**parse(char **args)
{
	int			index;
	size_t		cmds;
	t_command	**commands;

	commands = malloc(sizeof(t_command *) * get_commands_count(args));
	if (!commands)
		return (NULL);
	index = 0;
	cmds = -1;
	while (args[index])
	{
		
		commands[++cmds] = create_command(args, args[index], &index);
		if (index >= (int) array_length(args))
			break ;
		index++;
	}
	commands[++cmds] = NULL;
	parse_tokens(commands, args);
	free_array(args);
	return (complementary_parse(commands));
}
