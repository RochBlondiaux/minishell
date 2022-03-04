/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/04 09:59:05 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static char	*get_files(void)
{
	DIR				*d;
	struct dirent	*dir;
	char			*c;
	char			*hd;

	hd = working_directory();
	d = opendir(hd);
	if (d)
	{
		dir = readdir(d);
		c = ft_strdup("");
		while (dir)
		{
			if (dir->d_name[0] && dir->d_name[0] != '.')
				c = ft_strjoin_properly(c, ft_strjoin(dir->d_name, " "));
			dir = readdir(d);
		}
		closedir(d);
		return (c);
	}
	return (ft_strdup("*"));
}

void	expand_wildcards(t_app *app, char **input)
{
	int		i;
	char	*files;
	char	*r;

	i = -1;
	(void) app;
	r = *input;
	while (r[++i])
	{
		if (r[i] != '*')
			continue ;
		files = get_files();
		if (!files)
			continue ;
		r = replace_str(ft_strdup(r), "*", files);
	}
	*input = r;
}
