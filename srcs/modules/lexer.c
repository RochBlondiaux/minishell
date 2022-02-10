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

static void	print_token(t_token tokens)
{
	switch(tokens)
	{
		case AMPERSAND:
			printf("AMPERSAND ");
			break;
		case AND:
			printf("AND ");
			break;
		case PIPE:
			printf("PIPE ");
			break;
		case OR:
			printf("OR ");
			break;
		case REDIRECTION:
			printf("REDIRECTION ");
			break;
		case LITERAL:
			printf("LITERAL ");
			break;
		default:
			printf("ERROR\n");
	}
}

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
	j = -1;
	while (input[++i])
	{
/*		if (input[i] == 34)
		{
			tokens[++j] = LITERAL;
			while(input[i] != 34 && input[i])
			{
				i ++;
				tokens[++j] = LITERAL;
			}
			if (input[i] == 34)
				tokens[++j] = LITERAL;
		}
		else if (input[i] == 39)
		{
			tokens[++j] = LITERAL;
			while(input[i] != 39 && input[i])
			{
				i ++;
				tokens[++j] = LITERAL;
			}
			if (input[i] == 39)
				tokens[++j] = LITERAL;
		}*/
		tokens[++j] = get_token(input, i);
		if (tokens[j] == OR || tokens[j] == AND
			|| (input[i] == 60 && input[i + 1] == 60)
			|| (input[i] == 62 && input[i + 1] == 62))
			i ++;
		print_token(tokens[j]);
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

int is_in_quotes(int *quote, char c)
{
	if (c == '"' && *quote != 2)
	{
		if (*quote == 1)
			*quote = 0;
		else
			*quote = 1;
	}
	else if (c == '\'' && *quote != 1)
	{
		if (*quote == 2)
			*quote = 0;
		else
			*quote = 2;
	}
	return (!quote != 0);
}
