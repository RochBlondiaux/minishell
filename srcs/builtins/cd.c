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
	char	**dest;
	char	*temp;
	size_t	i;

	if (array_length(args) == 0)
		set_path(app, home_directory());
	else if (array_length(args) == 1)
	{
		i = -1;
		dest = ft_split(args[0], '/');
		while (dest[++i])
		{
			if (ft_strcmp(dest[i], ".."))
				set_path(app, parent(working_directory()));
			else
			{
				if (ft_strncmp(dest[i], "/", 1) && ft_strncmp(args[0], "/", 1) == 0)
				{
					temp = ft_strjoin("/", dest[i]);
					if (!set_path(app, path(temp)))
						error(app, ENOENT);
					free(temp);
				}
				else
					if (!set_path(app, path(dest[i])))
						error(app, ENOENT);
			}
			free(dest[i]);
		}
		free(dest);
	}
	else
		str_error(app, TOO_MANY_ARGUMENTS);
}
