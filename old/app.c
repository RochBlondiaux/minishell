/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 20:53:40 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:15 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	start_application(t_app *app)
{
	app->running = TRUE;
	handle_controls(app);
	launch_engine_loop(app);
}

t_app	*load_application(void)
{
	t_app	*app;

	app = malloc(sizeof(t_app *));
	app->error = FALSE;
	if (!app)
	{
		str_error(app, APP_INITIALIZATION_FAILED);
		exit(EXIT_FAILURE);
	}
	app->path = working_directory();
	return (app);
}

void	unload_application(t_app *app)
{
	if (FANCY_MODE)
		printf("%s%s\n", GREEN, EXIT_MESSAGE);
	if (app->sub)
		kill(app->sub, SIGKILL);
	free(app->path);
	free(app);
	exit(EXIT_SUCCESS);
}
