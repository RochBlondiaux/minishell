/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

char	**parse_quotes(char *raw)
{
	char	**args;

	args = ft_split(raw, ' ');

	/*new = malloc(sizeof (char *) * (get_args_count(args) + 1));
	if (!new)
	{
		free_array(args);
		return (NULL);
	}
	fill_args(raw, new);
	trim_args(new);
	free_array(args);*/
	return (args);
}