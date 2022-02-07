/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:38:54 by rblondia          #+#    #+#             */
/*   Updated: 2022/02/07 17:37:38 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_cd(t_app *app, char **args)
{
	char	*target;
	char	*tmp;

	if (array_length(args) == 1)
	{
		if (ft_strcmp(args[0], ".."))
		{
			tmp = working_directory();
			target = parent(tmp);
			free(tmp);
		}
		else
			target = path(args[0]);
	}
	else
		target = home_directory();
	if (!set_path(app, target))
		error(app, ENOENT);
}
