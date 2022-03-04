/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/04 09:58:30 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_app	*g_app;

void	ctrl_c_handler(int sig)
{
	t_app	*app;

	app = g_app;
	if (sig == SIGINT && app)
	{
		app->last_exit = 130;
		printf("\n");
		rl_on_new_line();
//		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	disable_signal(t_app *app)
{
	g_app = app;
	signal(SIGINT, ctrl_c_handler);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	enable_signal(t_app *app)
{
	g_app = app;
	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}
