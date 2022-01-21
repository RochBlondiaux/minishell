/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 23:45:08 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/21 14:19:11 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*env(char *name)
{
	char	*v;

	v = getenv(name);
	if (v == NULL)
		return (NULL);
	return (ft_strdup(v));
}

char	**process_env_vars(char **args)
{
	size_t	i;
	char	*tmp;

	i = -1;
	while (args[++i])
	{
		if (!args[i] || args[i][0] != '$')
			continue ;
		tmp = env(&args[i][1]);
		if (!tmp)
			continue ;
		free(args[i]);
		args[i] = tmp;
	}
	return (args);
}