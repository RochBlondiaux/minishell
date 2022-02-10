/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static t_token	get_token(char *input, size_t i)
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

static t_token	*tokenize(char *input)
{
	t_token	*tokens;
	size_t	i;
	size_t	j;
	size_t	len;

	len = ft_strlen(input);
	tokens = malloc(sizeof(t_token) * len);
	if (!tokens)
	{
		// TODO : afficher une erreur
		return (NULL);
	}
	i = -1;
	j = 0;
	while (input[++i])
	{
		tokens[j] = get_token(input, i);
		if (tokens[j] == OR || tokens[j] == AND ||
			(input[i] == 60 && input[i + 1] == 60) ||
				(input[i] == 62 && input[i + 1] == 62))
			i ++;
		j ++;
	}
	return (tokens);
}

t_token	*lexer(t_app *app, char *input, int *result)
{
	t_token	*tokens;

	if (!input || !app)
	{
		*result = -2;
		return (NULL);
	}
	if (ft_strlen(input) == 0)
	{
		*result = -1;
		return (NULL);
	}
	tokens = tokenize(input);
	return (tokens);
}
