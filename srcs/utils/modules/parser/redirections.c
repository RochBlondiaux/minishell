/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static t_redirection	get_type(char *a, size_t index)
{
	if (a[index])
	{
		if (a[index] == '>' && a[index + 1] && a[index + 1] == '>')
			return (APPENDER);
		if (a[index] == '<' && a[index + 1] && a[index + 1] == '<')
			return (DELIMITER);
		if (a[index] == '>')
			return (OUTPUT);
		if (a[index] == '<')
			return (INPUT);
	}
	return (NO);
}

static char	*set_redirection(t_command *cmd, char *raw,
							t_redirection redir, size_t index)
{
	char	*path;
	size_t	end;
	char	*tmp;

	while (raw[index] == ' ')
		index++;
	end = ft_strchr(&(raw[index]), ' ');
	if (end == 0)
		end = ft_strlen(raw) - index;
	path = ft_substr(raw, index, end);
	if (redir == APPENDER || redir == DELIMITER)
		tmp = ft_substr(raw, 0, index - 3);
	else
		tmp = ft_substr(raw, 0, index - 2);
	if (end == 0)
		end = ft_strlen(raw);
	tmp = ft_strjoin_properly(tmp, ft_substr(raw, index + end,
				ft_strlen(raw) - (index + end)));
	free(raw);
	if (redir == INPUT || redir == DELIMITER)
	{
		reset_str(&cmd->input_path, path);
		return (tmp);
	}
	reset_str(&cmd->output_path, path);
	return (tmp);
}

char	*parse_redirections(t_command *command, char *raw)
{
	size_t			i;
	t_redirection	redir;
	int				quotes;

	i = -1;
	quotes = 0;
	while (raw[++i])
	{
		is_in_quotes(&quotes, raw[i]);
		if (quotes != 0)
			continue ;
		redir = get_type(raw, i);
		if (redir != NO)
		{
			if (redir == APPENDER || redir == DELIMITER)
				i++;
			i++;
			raw = set_redirection(command, raw, redir, i);
		}
	}
	return (raw);
}
