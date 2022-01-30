/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:46:22 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:18 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*redirect_input(t_command *command)
{
	size_t	length;
	char	*input;
	char	**args;

	args = command->args;
	length = array_length(args);
	if (length == 0)
		return (NULL);
	return (read_file(app, args[length - 1]));
}

void redirect_output(t_command *command)
{
	(void) command;
}