/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:36:33 by rblondia          #+#    #+#             */
/*   Updated: 2022/02/07 15:34:53 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	count_types(char **args)
{
	size_t	index;
	size_t	types;

	index = -1;
	types = 0;
	while (args[++index])
	{
		while (args[index] && get_token(args[index]) == NONE)
			index++;
		types++;
		if (index >= array_length(args))
			break ;
		types++;
		continue ;
	}
	return (types);
}

static t_str_type *parse_types(char **args)
{
	size_t		index;
	size_t		j;
	t_str_type	*types;

	index = -1;
	j = -1;
	types = malloc(count_types(args) * sizeof(t_str_type));
	if (!types)
		return (NULL);
	while (args[++index])
	{
		while (args[index] && get_token(args[index]) == NONE)
			index ++;
		types[++j] = CMD;
		if (index >= array_length(args))
			break ;
		if (get_token(args[index]) != NONE)
			types[++j] = TOKEN;
		else
			types[++j] = UNKNOWN;
		continue;
	}
 	return (types);
}

static int free__(char **args, t_str_type *types)
{
	free_array(args);
	free(types);
	return (FALSE);
}

int	validate_syntax(char **args)
{
	t_str_type	*types;
	size_t		index;

	types = parse_types(args);
	if (!types)
	{
		free_array(args);
		return (FALSE);
	}
	if (types[0] != CMD || types[count_types(args) - 1] != CMD)
		return free__(args, types);
	index = -1;
	while (++index < count_types(args))
	{
		if (types[index] == TOKEN && types[index + 1] && types[index + 1] != CMD)
			return (FALSE);
	}
	free(types);
	return (TRUE);
}
