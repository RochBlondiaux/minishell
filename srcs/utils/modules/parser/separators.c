/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	is_separator(char *c)
{
	return (ft_strcmp_sensitive(c, "&")
		|| ft_strcmp_sensitive(c, "&&")
		|| ft_strcmp_sensitive(c, "|")
		|| ft_strcmp_sensitive(c, "||")
		|| ft_strcmp_sensitive(c, ";"));
}
