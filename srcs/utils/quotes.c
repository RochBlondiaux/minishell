/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:46:22 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:18 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_other_quote(char *arg, unsigned char c)
{
	size_t	i;

	i = 1;
	while(arg[i])
	{
		if (arg[i] == c)
		{
			printf("Found %c !\n", c);
			return (i);
		}
		i ++;
	}
	if (!arg[i])
		printf("No other one so display prompt!\n");
	return (i);
}

static char	*delete_quotes(char *arg)
{
	size_t	i;

	i = 0;
	while(arg[i])
	{
		if (arg[i] == 34)
			i += find_other_quote(&arg[i], 34);
		else if (arg[i] == 39)
			i += find_other_quote(&arg[i], 39);
		i ++;
	}
	return (arg);
}

char	*check_for_quotes(char *arg)
{
	char	**split;

	if ((arg[0] == 34 && arg[1] == 34 && !arg[2]) || ft_strcmp(arg, "''"))
	{
		free(arg);
		arg = ft_strdup("");
	}
	else if ((arg[0] == 34 && arg[1] == 34 && arg[2]))
	{
		split = ft_split(arg, 34);
		free(arg);
		arg = split[0];
		free(split);
	}
	else if ((arg[0] == 39 && arg[1] == 39 && arg[2]))
	{
		split = ft_split(arg, 39);
		free(arg);
		arg = split[0];
		free(split);
	}
	else
		arg = delete_quotes(arg);
	return(arg);
}