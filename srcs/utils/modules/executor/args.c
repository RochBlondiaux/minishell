/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

char	**get_executable_args(t_command *cmd)
{
	char	**a;
	size_t	i;

	a = malloc(sizeof(char *) * array_length(cmd->args) + 2);
	i = 0;
	a[0] = ft_strdup(cmd->name);
	i = -1;
	while (cmd->args[++i])
		a[i + 1] = ft_strdup(cmd->args[i]);
	a[i + 1] = NULL;
	return (a);
}
