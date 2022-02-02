/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:46:53 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*ft_lstnew(char *content)
{
	t_env	*thelist;

	thelist = malloc(sizeof(t_env));
	if (!thelist)
		return (NULL);
	thelist->variable = content;
	thelist->next = NULL;
	return (thelist);
}

void	free_list_env(t_env *env)
{
	(void) env;
}

t_env	*list_env(char **env)
{
	size_t	i;
	t_env	*env_var;

	i = 0;
	while (env[i])
	{
		env_var = ft_lstnew(env[i]);
		i ++;
	}
	return (env_var);
}
