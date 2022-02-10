/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	validate_token(t_token *tokens, t_token token,
					size_t index, t_token excepted)
{
	size_t	i;

	i = -1;
	while (tokens[++i])
	{
		if (tokens[i] == token
			&& tokens[i + index]
			&& tokens[i + index] == excepted)
			return (TRUE);
	}
	return (FALSE);
}
