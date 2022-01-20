/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 20:57:58 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/20 20:57:58 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	info(char *a)
{
	ft_putendl_fd(a, 1);
}

void	error(char *a)
{
	ft_putendl_fd(a, 2);
}