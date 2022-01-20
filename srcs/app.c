/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 20:53:40 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/20 22:06:26 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	start_application(t_app *app)
{
	app->running = TRUE;
	launch_engine_loop(app);
}

t_app	*load_application(void)
{
	t_app	*app;

	app = malloc(sizeof(t_app *));
	if (!app)
	{
		error(APP_INITIALIZATION_FAILED);
		exit(EXIT_FAILURE);
	}
	app->path = working_directory();
	return (app);
}

void	unload_application(t_app *app)
{
	free(app->path);
	free(app);
}
