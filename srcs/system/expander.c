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

static void expand_single(t_command *command)
{
	int		index;
	char	*tmp;
	char	*vars;

	index = -1;
	while (command->args[++index])
	{
		if (!is_envars(command->args[index]))
			continue ;
		vars = ft_substr(command->args[index], 1, ft_strlen(command->args[index]));
		tmp = env(vars);
		free(vars);
		if (!tmp)
			continue ;
		printf("Envars: %s to %s\n", command->args[index], tmp);
		free(command->args[index]);
		command->args[index] = tmp;
	}
}

// TODO : not sure if we're supposed to expand wildcards (ex: cat README.*)
void	expand(t_command **commands)
{
	size_t	index;

	index = -1;
	while (commands[++index])
		expand_single(commands[index]);
}