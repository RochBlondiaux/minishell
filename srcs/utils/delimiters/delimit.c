/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	nb_delims(t_redir *r)
{
	t_redir	*tmp;
	int		i;

	tmp = r;
	i = 0;
	while (tmp)
	{
		if (tmp->type == DELIMITER)
			i ++;
		tmp = tmp->next;
	}
	return (i);
}

static char	**are_the_del(t_redir *r)
{
	char	**dest;
	t_redir	*tmp;
	size_t	i;

	dest = malloc(sizeof(char *) * (nb_delims(r) + 1));
	if (!dest)
		return (NULL);
	tmp = r;
	i = -1;
	while (tmp)
	{
		if (tmp->type == DELIMITER)
			dest[++i] = ft_strdup(tmp->path);
		tmp = tmp->next;
	}
	dest[++i] = NULL;
	return (dest);
}

static int	is_a_delim(t_redir *r)
{
	t_redir	*tmp;

	tmp = r;
	while (tmp)
	{
		if (tmp->type == DELIMITER)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

static char	*print_delim(t_app *app, char **delimitors)
{
	char	*line;
	char	*args;
	int		i;
	size_t	j;

	i = -1;
	j = 0;
	line = readline(DELIMIT_PROMPT);
	args = ft_strdup("");
	while (line)
	{
		if (!line)
			break ;
		if (ft_strcmp_sensitive(line, delimitors[j]) == 0)
		{
			i = -1;
			j = -1;
			args = ft_strjoin_properly(args, ft_strdup(line));
			args = ft_strjoin_properly(args, ft_strdup("\n"));
		}
		else if (ft_strcmp_sensitive(line, delimitors[j]) != 0)
			i += 1;
		if (i == ((int)array_length(delimitors) - 1))
			break ;
		free(line);
		line = readline(get_right_prompt(app));
		j ++;
	}
	free_array(delimitors);
	if (!line)
		return (NULL);
	free(line);
	return (args);
}

char	*delimit_all(t_app *app, t_command *cmd)
{
	char	**delimitors;
	int		fd;
	char	*a;

	if (is_a_delim(cmd->redirections) == 0)
		return (NULL);
	delimitors = are_the_del(cmd->redirections);
	a = print_delim(app, delimitors);
	if (!a)
		return (NULL);
	fd = open("jas2ASSD66aS6gg56q6ev3as3dxx6v6cxv565",
			O_CREAT | O_RDWR | O_APPEND, S_IRUSR
			| S_IRGRP | S_IWGRP | S_IWUSR);
	ft_putstr_fd(a, fd);
	close(fd);
	free(a);
	return ("jas2ASSD66aS6gg56q6ev3as3dxx6v6cxv565");
}
