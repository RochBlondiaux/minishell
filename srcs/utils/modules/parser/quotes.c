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

/*static size_t	get_args_count(char **args)
{
	size_t	i;
	size_t	j;
	size_t	c;
	int		quotes;

	i = -1;
	c = 0;
	quotes = 0;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
			is_in_quotes(&quotes, args[i][j]);
		if (quotes == 0)
			c++;
	}
	return (c);
}

static void	fill_args(char *raw, char **new)
{
	size_t	i;
	int		q;
	size_t	start;
	size_t	n;

	i = -1;
	q = 0;
	start = 0;
	n = -1;
	while (raw[++i])
	{
		if ((q == '\'' && raw[i] == q)
			|| (q == '"' && raw[i] == q)
			|| (q == 0 && raw[i] == ' '))
		{
			if (i - start <= 0)
				continue ;
			q = 0;
			new[++n] = ft_substr(raw, start, i - start);
			start = i + 1;
			continue ;
		}
		if ((raw[i] == '\'' || raw[i] == '"' || raw[i] == ' ') && q == 0)
		{
			start = i + 1;
			if (raw[i] != ' ')
				q = raw[i];
		}
	}
	if (start <= ft_strlen(raw))
		new[n++] = ft_substr(raw, start, ft_strlen(raw) - start);
	new[n++] = NULL;
}

static void	trim_args(char **args)
{
	size_t	i;

	i = -1;
	while (args[++i])
		args[i] = ft_strtrim(args[i], " ");
}

char	**parse_quotes(char *raw)
{
	char	**args;
	char	**new;

	args = ft_split(raw, ' ');
	new = malloc(sizeof (char *) * (get_args_count(args) + 1));
	if (!new)
	{
		free_array(args);
		return (NULL);
	}
	fill_args(raw, new);
	trim_args(new);
	free_array(args);
	return (new);
}*/

static int	find_other_quote(char *arg, unsigned char c)
{
	size_t	i;

	i = 1;
	while(arg[i])
	{
		if (arg[i] == c)
			return (i);
		i ++;
	}
	if (arg[i])
		return (i);
	else return (-1);
}

static char	*delete_test(char *arg, int c)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = -1;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(arg) - 2));
	while(arg[++i])
	{
		if (arg[i] == c)
			continue;
		new[j] = arg[i];
		j ++;
	}
	new[j] = '\0';
	free(arg);
	return (new);
}

static char	*delete_quotes(char *arg)
{
	size_t	i;
	int		j;

	i = 0;
	j = -1;
	while(arg[i])
	{
		if (arg[i] == 34)
		{
			i += find_other_quote(&arg[i], 34);
			j = 34;
			break;
		}
		else if (arg[i] == 39)
		{
			i += find_other_quote(&arg[i], 39);
			j = 39;
			break ;
		}
		i ++;
	}
	if (j != -1)
		arg = delete_test(arg, j);
	else
		arg = ft_strtrim(arg, "'\"");
	return (arg);
}

static char	*check_for_quotes(char *arg)
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
		arg = ft_strdup(split[0]);
		free(split);
	}
	else
		arg = delete_quotes(arg);
	return(arg);
}

char	**parse_quotes(char *raw)
{
	char	**args;
	size_t	i;

	args = ft_split(raw, ' ');
	i = 0;
	while(args[i])
	{
		args[i] = check_for_quotes(args[i]);
		i ++;
	}
	return (args);
}
