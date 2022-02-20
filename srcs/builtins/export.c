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
	int		err;
	size_t	i;

	if (print_right_output(app, cmd))
		return ;
	i = -1;
	err = 0;
	while (cmd->args[++i])
	{
		if (cmd->args[i][0] != '$' && get_env(app, cmd->args[i]) != NULL)
			continue ;
		if (check_new_env(app, cmd->args[i]) != 0)
		{
			err ++;
			continue ;
		}
		new = create_map_element(cmd->args[i]);
		if (new)
			set_env(app, new->key, new->value);
		free_env(new);
	}
	if (err != 0)
		cmd->status = 1;
	else
		cmd->status = 0;
}
