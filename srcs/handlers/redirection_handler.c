/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:52:44 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/22 15:07:54 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_input_redirection(t_app *app, char **args)
{
	size_t	lenght;
	char	*input;

	lenght = array_length(args);
	if (lenght == 0)
		return (NULL);
	input = read_file(app, args[lenght - 1]);
	return (input);
}

void	handle_output_redirection(t_app *app, char **args)
{
	(void) app;
	(void) args;
}
