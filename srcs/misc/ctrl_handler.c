/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:14:44 by rblondia          #+#    #+#             */
/*   Updated: 2022/02/07 17:15:41 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_app	*g_app;

static void	exit_handler(int a)
{
	(void) a;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	do_nothing(int a)
{
	(void) a;
	rl_on_new_line();
}

void	handle_ctrl(t_app *app)
{
	g_app = app;
	signal(SIGINT, exit_handler);
	signal(SIGQUIT, do_nothing);
}
