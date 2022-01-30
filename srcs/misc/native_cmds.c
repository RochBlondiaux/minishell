/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   native_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:46:22 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:18 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// TODO : handle input redirection
// -> might be executed in another function (bc of the pipe() function)
int	execute_native_command(t_app *app, t_command *cmd)
{
	int		ret;
	char	**tmp;
	int		status;

	ret = fork();
	if (ret < 0)
		str_error(app, OCCURRED_ERROR);
	else if (ret == 0)
	{
		tmp = add_array_element(cmd->args, cmd->name);
		execv(get_command_path(cmd->name), tmp);
		free_array(tmp);
	}
	waitpid(ret, &status, 0);
	kill(ret, SIGKILL);
	app->error = WEXITSTATUS(status);
	return (ret);
}