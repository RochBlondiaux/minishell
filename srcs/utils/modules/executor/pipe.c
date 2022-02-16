/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static t_pipe	*create_pipeline(void)
{
	t_pipe	*p;

	p = malloc(sizeof(t_pipe));
	if (!p)
		return (NULL);
	p->backup = 0;
	p->in = 0;
	p->out = 0;
	return (p);
}

static void	update_pipeline(t_app *app, t_pipe *p)
{
	int		fd[2];

	if (pipe(fd) == -1)
	{
		error(app, "-minishell", PIPE_ERROR);
		return ;
	}
	p->in = fd[0];
	p->out = fd[1];
}

void	init_pipeline(t_app *app, t_pipe **pipe)
{
	if (!*pipe)
		*pipe = create_pipeline();
	update_pipeline(app, *pipe);
}
