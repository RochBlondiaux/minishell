/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:38:54 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_echo(char **args)
{
	int		mode;
	size_t	i;
	size_t	l;

	i = -1;
	mode = 0;
	l = array_length(args);
	if (l > 0 && ft_strcmp(args[0], "-n"))
	{
		mode = 1;
		i += 1;
	}
	while (args[++i])
	{
		if (i == l - 1)
			printf("%s", args[i]);
		else
			printf("%s ", args[i]);
	}
	if (l > 0)
	{
		if (mode)
			printf("%s%s%%%s", BOLD, "\033[3;107;30m", RESET);
		printf("\n");
	}
}
