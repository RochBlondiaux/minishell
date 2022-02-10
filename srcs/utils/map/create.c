/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env	*create_map_element(char *entry)
{
	char	**e;
	t_env	*env;

	if (ft_strchr(entry, '=') <= 0)
		return (NULL);
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	e = ft_split(entry, '=');
	env->key = ft_strdup(e[0]);
	if (array_length(e) >= 2)
		env->value = ft_strdup(e[1]);
	else
		env->value = ft_strdup(" ");
	env->next = NULL;
	free_array(e);
	return (env);
}
