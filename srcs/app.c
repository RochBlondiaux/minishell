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

t_app	*load_application(char **env)
{
	t_app	*app;

	(void) env;
	app = malloc(sizeof(t_app));
	if (!app)
	{
		str_error(app, APP_INITIALIZATION_FAILED);
		exit(EXIT_FAILURE);
	}
	app->path = working_directory();
	app->env = init_env_map(env);
	app->error = FALSE;
	app->exit = 0;
	return (app);
}

void	start_application(t_app *app)
{
	app->running = TRUE;
	handle_ctrl(app);
	start_engine(app);
}

void	stop_application(t_app *app)
{
	printf("%s%s\n", GREEN, EXIT_MESSAGE);
	free_map(&app->env);
	free(app->path);
	free(app);
}
