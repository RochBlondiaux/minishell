/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 20:53:40 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/21 14:36:46 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	commands_length(t_command **commands)
{
	size_t	i;

	i = 0;
	while (commands[i])
		i++;
	return (i);
}

void	free_commands(t_command **commands)
{
	size_t		i;
	t_command	*cmd;

	i = -1;
	while (commands[++i])
	{
		cmd = commands[i];
		free(cmd->name);
		free_array(cmd->args);
		free(cmd);
	}
	free(commands);
}

static	size_t	arguments_count(char **args, char *name)
{
	size_t	index;
	size_t	arguments;

	index = 0;
	arguments = 0;
	while (args[index] && !ft_strcmp(name, args[index]))
		index++;
	while (args[index] && !is_separator(args[index]))
	{
		arguments++;
		index++;
	}
	return (arguments - 1);
}

static char	**get_command_arguments(char **args, char *name, int *ret)
{
	size_t	index;
	size_t	arguments;
	char	**args_;

	index = 0;
	arguments = 0;
	args_ = malloc(sizeof(char *) * (arguments_count(args, name) + 1));
	while (args[index] && !ft_strcmp(name, args[index]))
		index++;
	index++;
	while (args[index] && !is_separator(args[index]))
	{
		args_[arguments] = ft_strdup(args[index]);
		printf("Argument #%zu: %s\n", arguments, args_[arguments]);
		arguments++;
		index++;
	}
	*ret = index;
	args_[arguments] = NULL;
	return (args_);
}

t_command	*create_command(char **args, char *name, int *index)
{
	t_command	*cmd;

	if (!args || !name)
		return (NULL);
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->name = ft_strdup(name);
	printf("------ [%s] ------\n", cmd->name);
	cmd->args = get_command_arguments(args, name, index);
	printf("\n");
	return (cmd);
}
