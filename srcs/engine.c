/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 20:53:40 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:15 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	start_engine(t_app *app)
{
	char	*line;

	while (app->running)
	{
		line = readline(get_prompt_symbol(app));
		app->error = FALSE;
		if (!line)
			break ;
		else if (ft_strlen(line) == FALSE)
		{
			app->error = TRUE;
			continue ;
		}
		if (!app->error)
			add_history(line);
		free(line);
	}
}