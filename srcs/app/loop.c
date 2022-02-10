/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c 	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	start_application_loop(t_app *app)
{
	char	*line;
	int		rv;

	while (app->running)
	{
		line = readline(get_prompt_symbol(app));
		app->exit = 0;
		rv = runtime(app, line);
		if (!line)
			break ;
		if (!rv || !ft_strlen(line))
		{
			free(line);
			continue ;
		}
		add_history(line);
		free(line);
	}
}
