/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:23:02 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_read(int fd)
{
	char	*buffer;
	int		red;

	buffer = malloc(READ_BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	red = read(fd, buffer, READ_BUFFER_SIZE);
	if (red <= 0)
	{
		free (buffer);
		return (NULL);
	}
	buffer[red] = '\0';
	return (buffer);
}

char	*read_file(t_app *app, char *path)
{
	int		fd;
	char	*content;
	char	*tmp;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		error(app, EBADF);
		return (NULL);
	}
	tmp = ft_read(fd);
	content = NULL;
	while (tmp)
	{
		if (!content)
			content = tmp;
		else
			content = ft_strjoin_properly(content, tmp);
		tmp = ft_read(fd);
	}
	return (content);
}

void	write_output(t_app *app, t_command *cmd)
{
	int	fd;

	if (cmd->appender)
		fd = open(cmd->output_path,
				O_CREAT | O_RDWR | O_APPEND, S_IRUSR
				| S_IRGRP | S_IWGRP | S_IWUSR);
	else
		fd = open(cmd->output_path,
				O_CREAT | O_RDWR | O_TRUNC, S_IRUSR
				| S_IRGRP | S_IWGRP | S_IWUSR);
	if (fd < 0)
	{
		error(app, errno);
		return ;
	}
	ft_putstr_fd(cmd->output, fd);
	close(fd);
}
