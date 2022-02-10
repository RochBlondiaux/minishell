/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_duplicated(t_token *tokens)
{
	size_t	index;

	index = -1;
	while (tokens[++index])
	{
		if (tokens[index] != LITERAL && tokens[index + 1] != LITERAL)
			return (FALSE);
	}
	return (TRUE);
}

static int	args_check(char *input)
{
	char	**args;
	size_t	index;

	args = ft_split(input, ' ');
	if (!args)
		return (FALSE);
	index = -1;
	while (args[++index])
	{
		if (args[index + 1]
			&& (get_real_token(args[index]) != LITERAL
				&& get_real_token(args[index + 1]) != LITERAL))
		{
			free_array(args);
			return (FALSE);
		}
	}
	free_array(args);
	return (TRUE);
}

int	syntaxer(char *input, t_token *tokens)
{
	int	result;

	result = TRUE;
	if ((tokens[0] != LITERAL && tokens[0] != REDIRECTION)
		|| tokens[tokens_length(tokens) - 1] != LITERAL
		|| !check_duplicated(tokens)
		|| !args_check(input))
		result = FALSE;
	free(tokens);
	if (!result)
		errno = ENOTSUP;
	return (result);
}
