/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                           :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	error(t_app *app, char *name, char *error)
{
	ft_putstr_fd(name, 2);
	ft_putchar_fd(':', 2);
	ft_putstr_fd(error, 2);
	app->exit = 1;
}

void	str_error(t_app *app, char *error)
{
	perror(error);
	app->exit = 1;
}
