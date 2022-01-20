/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 20:53:40 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/20 21:02:34 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_app	*load_application(void)
{
	t_app	*app;

	app = malloc(sizeof(t_app *));
	if (!app)
	{
		error(APP_INITIALIZATION_FAILED);
		exit(EXIT_FAILURE);
	}
	app->prompt_symbol = ft_strjoin(GREEN, PROMPT_SYMBOL);
	return (app);
}

void	unload_application(t_app *app)
{
	free(app->prompt_symbol);
	free(app);
}