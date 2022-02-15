/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_export(t_app *app, t_command *cmd)
{
	t_env	*new;

	if (array_length(cmd->args) == 0)
	{
		print_sorted_map(app->env);
		cmd->status = 0;
		return ;
	}
	new = create_map_element(cmd->args[0]);
	set_env(app, new->key, new->value);
	free(new->key);
	free(new->value);
	free(new);
}
