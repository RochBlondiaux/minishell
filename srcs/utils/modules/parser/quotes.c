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

static size_t	get_args_count(char **str)
{
	size_t	i;
	size_t	len;
	size_t	j;
	int		quote;

	i = 0;
	len = 0;
	quote = 0;
	while (str[i])
	{
		j = -1;
		while (str[i][++j])
			is_in_quotes(&quote, str[i][j]);
		if (quote == 0)
			len++;
		i ++;
	}
	return (len);
}

static int	get_quote_in_here(char *s)
{
	size_t	i;

	i = -1;
	if (!s)
		return (-1);
	while (s[++i])
	{
		if (s[i] == '"' || s[i] == '\'')
			return (i);
	}
	return (-1);
}

static int	nb_quotes(char *s, int quote)
{
	int		i;
	size_t	j;

	i = 0;
	j = -1;
	while (s[++j])
	{
		if (s[j] == quote)
			i ++;
	}
	return (i);
}

static char	*sup_quote(char *arg)
{
	char	*dest;
	int		quote;
	size_t	j;
	size_t	i;

	quote = -1;
	j = -1;
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '"' || arg[i] == '\'')
		{
			quote = arg[i];
			break ;
		}
	}
	if (quote == -1)
		return (arg);
	else
	{
		i = -1;
		dest = malloc(sizeof(char) * (ft_strlen(arg)
					- nb_quotes(arg, quote) + 1));
		while (arg[++i])
		{
			if (arg[i] != quote)
				dest[++j] = arg[i];
		}
		dest[++j] = '\0';
	}
	free(arg);
	return (dest);
}

static int	is_quote_in_here(char *s)
{
	int		same_quote;
	int		quote;
	size_t	i;

	i = -1;
	quote = 0;
	if (!s)
		return (-1);
	while (s[++i])
	{
		if ((s[i] == '"' || s[i] == '\'') && quote % 2 == 0)
		{
			quote ++;
			same_quote = s[i];
			i ++;
		}
		if (s[i] == same_quote)
		{
			quote ++;
			continue ;
		}
	}
	if (quote % 2 == 0 || quote == 0)
		return (0);
	return (-1);
}

static void	fill(char **args, char **raw)
{
	size_t	i;
	size_t	j;
	int		quote;

	i = -1;
	j = -1;
	quote = 0;
	while (raw[++i])
	{
		if (quote == 0 && is_quote_in_here(raw[i]) == 0)
			args[++j] = sup_quote(ft_strdup(raw[i]));
		else
		{
			j ++;
			quote = raw[i][get_quote_in_here(raw[i])];
			while (quote != 0 && raw[i] && raw[i + 1])
			{
				if (!args[j])
					args[j] = ft_strjoin(raw[i], " ");
				else
					args[j] = ft_strjoin_properly(args[j], ft_strjoin(raw[i], " "));
				if (get_quote_in_here(raw[i + 1]) != -1)
				{
					args[j] = ft_strjoin_properly(args[j], ft_strjoin(raw[i + 1], " "));
					args[j] = sup_quote(args[j]);
					quote = 0;
				}
				i++;
			}
		}
	}
	args[++j] = NULL;
}

char	**parse_quotes(char *raw)
{
	char	**args;
	char	**split;

	split = ft_split(raw, ' ');
	args = malloc(sizeof(char *) * (get_args_count(split) + 1));
	if (!args)
	{
		free_array(split);
		return (NULL);
	}
	fill(args, split);
	free_array(split);
	return (args);
}
