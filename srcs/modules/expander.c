/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/04 10:22:20 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	expand(t_app *app, t_command **commands)
{
	size_t	i;

	i = -1;
	if (commands[0] && !commands[0]->name[0] && !commands[1])
	{
		app->last_exit = 127;
		errno = 2;
		str_error(app, "");
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
