/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 20:53:40 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/20 23:42:51 by rblondia         ###   ########.fr       */
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
	app->error = 0;
	return (app);
}

void	unload_application(t_app *app)
{
	if (app->path)
		free(app->path);
	free(app);
}
