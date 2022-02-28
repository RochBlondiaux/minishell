/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
				return (str + i);
			j++;
		}
	}
	return (FALSE);
}

char	*replace_str(char *str, char *find, char *replace)
{
	char	*pos;
	char	temp[1024];
	int		index;
	int		owlen;

	owlen = ft_strlen(find);
	if (ft_strcmp(find, replace) < 0)
		return (str);
	pos = ft_strstr(str, find);
	while (pos)
	{
		ft_strlcpy(temp, str, ft_strlen(temp) + ft_strlen(str));
		index = pos - str;
		str[index] = '\0';
		ft_strcat(str, replace);
		ft_strcat(str, temp + index + owlen);
		pos = ft_strstr(str, find);
	}
	return (str);
}
