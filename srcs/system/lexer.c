/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:46:22 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/26 16:46:22 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Parse argument from inputted line.
 * @param app application instance.
 * @param input inputted line.
 * @param result -2 if line is null, -1 if line is empty
 * & 0 if everything works as excepted.
 * @return t_command structure filled.
 */
char	**lexer(t_app *app, char *input, int *result)
{
	if (!input || !app)
	{
		*result = -2;
		return (NULL);
	}
	if (ft_strlen(input) == 0)
	{
		app->error = TRUE;
		*result = -1;
		return (NULL);
	}
	return (ft_split(input, ' '));
}
