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

static int	check_existing_cd(t_app *app, char *dest, char **args)
{
	char	*temp;

	if (ft_strcmp(dest, ".."))
	{
		if (!set_path(app, parent(working_directory())))
		{
			error(app, ENOENT);
			return (-1);
		}
	}
	else
	{
		if (ft_strncmp(dest, "/", 1) && ft_strncmp(args[0], "/", 1) == 0)
		{
			temp = ft_strjoin("/", dest);
			if (!set_path(app, path(temp)))
			{
				error(app, ENOENT);
				return (-1);
			}
			free(temp);
		}
		else
		{
			if (!set_path(app, path(dest)))
			{
				error(app, ENOENT);
				return (-1);
			}
		}
	}
	return (0);
}

void	builtin_cd(t_app *app, char **args)
{
	char	**dest;
	size_t	i;

	if (array_length(args) == 0)
		set_path(app, home_directory());
	else if (array_length(args) == 1)
	{
		i = -1;
		dest = ft_split(args[0], '/');
		while (dest[++i])
		{
			if (check_existing_cd(app, dest[i], args) != 0)
			{
				free_array(dest);
				return ;
			}
		}
		free_array(dest);
	}
	else
		str_error(app, TOO_MANY_ARGUMENTS);
}
