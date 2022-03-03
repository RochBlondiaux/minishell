/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                          :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by lfilloux          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_env	*check_existence(t_env *env, char *name)
{
	t_env	*tmp;

	while (env)
	{
		tmp = (env)->next;
		if (tmp && (ft_strcmp_sensitive(tmp->key, name)
				|| ft_strcmp_sensitive(tmp->value, name)))
			return (tmp);
		env = tmp;
	}
	return (NULL);
}

static int	check_env(t_app *app, char *arg)
{
	t_env	*env;

	env = check_existence(app->env, arg);
	if (!env)
		return (0);
	return (1);
}

int	check_new_env(t_app *app, char *var)
{
	if (!var[0])
		return (1);
	if (check_env(app, var) != 0)
	{
		error(app, "export", INVALID_CONTEXT);
		return (1);
	}
	if (var[0] == '=')
	{
		error(app, "export", INVALID_CONTEXT);
		return (1);
	}
	return (0);
}

static int	check_null(t_command *cmd)
{
	size_t	i;
	size_t	count;
	size_t	wrong;

	i = -1;
	count = 0;
	wrong = 0;
	while (cmd->args[++i])
	{
		if (!cmd->args[i][0])
		{
			count ++;
			continue ;
		}
		if (cmd->args[i][0] == '$')
			wrong ++;
		else if (cmd->args[i][0] != '$')
			return (1);
	}
	if ((i == count && i != 0) || (count != 0 && wrong != 0))
		return (2);
	else if (i == wrong && i != 0)
		return (3);
	return (0);
}

int	print_right_output(t_app *app, t_command *cmd)
{
	int	ret;

	ret = check_null(cmd);
	if (!ret)
	{
		print_sorted_map(app->env);
		cmd->status = 0;
		return (1);
	}
	if (ret == 2)
	{
		error(app, "export", INVALID_CONTEXT);
		cmd->status = 1;
		return (1);
	}
	if (ret == 3)
	{
		print_sorted_map(app->env);
		cmd->status = 0;
		return (1);
	}
	return (0);
}
