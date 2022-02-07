/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:46:22 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:18 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_commands(t_command **commands)
{
	size_t	i;

	i = -1;
	while (commands[++i])
	{
		if (i > 0)
			commands[i]->previous = commands[i - 1];
		if (i < commands_length(commands) - 1)
			commands[i]->next = commands[i + 1];
		commands[i]->status = 0;
	}
}
