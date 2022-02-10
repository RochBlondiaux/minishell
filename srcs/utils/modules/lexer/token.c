/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static int	which_token(char *input, size_t i)
{
	if (input[i] == 38 && input[i + 1] != 38 && input[i -1] != 38)
		return (0);
	else if (input[i] == 38 && input[i + 1] == 38)
		return (1);
	else if (input[i] == 124 && input[i + 1] != 124 && input[i -1] != 124)
		return (2);
	else if (input[i] == 124 && input[i + 1] == 124)
		return (3);
	else if (input[i] == 60 && input[i + 1] != 60 && input[i -1] != 60)
		return (4);
	else if (input[i] == 62 && input[i + 1] != 62 && input[i - 1] != 62)
		return (4);
	else if (input[i] == 60 && input[i + 1] == 60)
		return (4);
	else if (input[i] == 62 && input[i + 1] == 62)
		return (4);
	return (-1);
}

t_token	get_token(char *input, size_t i)
{
	if (input[i] == 59)
		return (SEMI_COLON);
	else if (which_token(input, i) == 0)
		return (AMPERSAND);
	else if (which_token(input, i) == 1)
		return (AND);
	else if (which_token(input, i) == 2)
		return (PIPE);
	else if (which_token(input, i) == 3)
		return (OR);
	else if (which_token(input, i) == 4)
		return (REDIRECTION);
	return (LITERAL);
}
