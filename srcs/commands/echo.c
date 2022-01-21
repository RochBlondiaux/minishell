/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:38:54 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/20 23:38:10 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	m_echo(char **args)
{
	int		mode;
	size_t	i;
	size_t	l;

	i = 0;
	mode = 0;
	l = array_length(args);
	if (l >= 2 && ft_strcmp(args[1], "-n"))
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
	if (l > 1)
	{
		if (mode)
			printf("%s%s%%%s", BOLD, "\033[3;107;30m", RESET);
		printf("\n");
	}
}