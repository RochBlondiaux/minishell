/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_unset(t_app *app, t_command *cmd)
{
	size_t	i;
	int		nb_error;

	if (array_length(cmd->args) < 1)
	{
		error(app, "unset", NOT_ENOUGH_ARGS);
		return ;
	}
	i = -1;
	nb_error = 0;
	while (cmd->args[++i])
		nb_error += remove_map_element(app, &app->env, cmd->args[i]);
	if (nb_error != 0)
		cmd->status = 1;
	else
		cmd->status = 0;
}
