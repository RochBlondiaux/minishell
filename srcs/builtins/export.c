/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:38:54 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid(char *arg)
{
	size_t	i;

	i = 0;
	if (!arg || (unsigned char)arg[0] == '=')
		return (0);
	while (ft_isalpha(arg[i]))
		i++;
	if ((unsigned char)arg[i] == '=' && (unsigned char)arg[i + 1] != '=')
		return (1);
	return (0);
}

void	builtin_export(t_app *app, char **args)
{
	if (is_valid(args[0]) == 1)
		add_env(&app->env, create_env_vars(args[0]));
	else
		return ;
}
