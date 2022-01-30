/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:23:02 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_path(t_app *app, char *a)
{
	if (!a || !exists(a))
		return (FALSE);
	free(app->path);
	app->path = a;
	return (chdir(a) == FALSE);
}

char	*get_prompt_symbol(t_app *app)
{
	if (app->error)
		return (ERROR_PROMPT_SYMBOL);
	return (PROMPT_SYMBOL);
}
