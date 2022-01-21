/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outputs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:07:00 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/21 11:12:12 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error(t_app *app, int code)
{
	perror(strerror(code));
	app->error = 1;
}

void	str_error(t_app *app, char *error)
{
	ft_putendl_fd(error, 2);
	app->error = 1;
}