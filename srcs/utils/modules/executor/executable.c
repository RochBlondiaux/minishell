/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	find_executable(t_app *app, t_command *cmd)
{
	char	*bin;

	if (is_builtin(cmd))
		return (TRUE);
	bin = get_executable(app, cmd, cmd->name);
	if (!bin)
		return (FALSE);
	if (!bin[0])
	{
		free(bin);
		return (-1);
	}
	reset_str(&cmd->executable, bin);
	return (TRUE);
}
