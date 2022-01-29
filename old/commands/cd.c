/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:38:54 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/21 13:52:02 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	m_cd(t_app *app, char **args)
{
	char	*target;
	char	*tmp;

	if (array_length(args) == 1)
	{
		if (ft_strcmp(args[0], ".."))
		{
			tmp = working_directory();
			target = parent(tmp);
		}
		else
			target = path(args[0]);
	}
	else
		target = home_directory();
	if (!set_path(app, target))
		error(app, ENOENT);
}
