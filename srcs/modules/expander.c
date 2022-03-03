/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	expand(t_app *app, t_command **commands)
{
	size_t	i;

	i = -1;
	if (commands[0]->name && !commands[0]->name[0]
		&& !commands[1])
	{
		errno = 13;
		str_error(app, "");
		app->last_exit = 126;
		return (FALSE);
	}
	while (commands[++i])
	{
		if (!expand_output(app, commands[i])
			|| !expand_input(app, commands[i]))
			return (FALSE);
	}
	return (TRUE);
}
