/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:46:22 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:18 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_envars(char *a)
{
	return (ft_strlen(a) > 0 && a[0] == '$');
}

static void	expand_env_vars(t_app *app, t_command *command)
{
	int		index;
	t_env	*var;

	index = -1;
	while (command->args[++index])
	{
		if (!is_envars(command->args[index]))
			continue ;
		var = get_env(app->env, &command->args[index][1]);
		free(command->args[index]);
		if (!var)
			command->args[index] = ft_strdup("");
		else
			command->args[index] = ft_strdup(var->value);
	}
}

static void	expand_input(t_app *app, t_command *cmd)
{
	if (!cmd->input_path
		|| !cmd->input_path[0])
		return ;
	free(cmd->input);
	cmd->input = read_file(app, cmd->input_path);
}

void	expand(t_app *app, t_command **commands)
{
	size_t	index;

	index = -1;
	while (commands[++index])
	{
		expand_env_vars(app, commands[index]);
		expand_input(app, commands[index]);
	}
}
