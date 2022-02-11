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

static void	set_redirection(t_command *cmd, char **raw, t_redirection redir, size_t index)
{
	char	*path;

	if (*raw[index] == ' ')
		index++;
	path = ft_substr(*raw, index, index + ft_strchr(&*raw[index], ' '));
	// TODO : REMOVE redirection from raw
	if (redir == INPUT || redir == DELIMITER)
	{
		free(cmd->input_path);
		cmd->input_path = path;
		return ;
	}
	free(cmd->output_path);
	cmd->output_path = path;
}

void	parse_redirections(t_command *command, char *raw)
{
	size_t			i;
	t_redirection	redir;

	i = -1;
	(void) command;
	while (raw[++i])
	{
		redir = get_type(raw, i);
		if (redir != NO)
		{
			if (redir == APPENDER || redir == DELIMITER)
				i++;
			i++;
			set_redirection(command, &raw, redir, i);
			printf("Raw : %s\n", raw);
		}
	}
}
