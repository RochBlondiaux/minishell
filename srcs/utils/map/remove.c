/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	free_target(t_env *tmp)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

int	remove_map_element(t_app *app, t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	if (!tmp && ft_strcmp_sensitive(tmp->key, key))
	{
		*env = tmp->next;
		free_target(tmp);
		return (1);
	}
	while (tmp && !ft_strcmp_sensitive(tmp->key, key))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		error(app, UNSET_ERROR, "");
		return (1);
	}
	prev->next = tmp->next;
	free_target(tmp);
	return (0);
}
