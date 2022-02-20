/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*check_existence(t_env *env, char *name)
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

static int	check_new_env(t_app *app, char *var)
{
	if (!var[0])
		return (1);
	if (check_env(app, var) != 0)
	{
		error(app, "export", "not valid in this context: ");
		return (1);
	}
	if (var[0] == '=')
	{
		error(app, "export", "not valid in this context: ");
		return (1);
	}
	return (0);
}

static int	all_null(t_command *cmd)
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

void	builtin_export(t_app *app, t_command *cmd)
{
	t_env	*new;
	int		err;
	size_t	i;

	if (!all_null(cmd))
	{
		print_sorted_map(app->env);
		cmd->status = 0;
		return ;
	}
	if (all_null(cmd) == 2)
	{
		error(app, "export", "not valid in this context: ");
		cmd->status = 1;
		return ;
	}
	if (all_null(cmd) == 3)
	{
		print_sorted_map(app->env);
		cmd->status = 0;
		return ;
	}
	i = -1;
	err = 0;
	while (cmd->args[++i])
	{
		if (cmd->args[i][0] != '$' && get_env(app, cmd->args[i]) != NULL)
			continue ;
		if (check_new_env(app, cmd->args[i]) != 0)
		{
			err ++;
			continue ;
		}
		new = create_map_element(cmd->args[i]);
		if (new)
		{
			set_env(app, new->key, new->value);
			free(new->key);
			free(new->value);
		}
		free(new);
	}
	if (err != 0)
		cmd->status = 1;
	else
		cmd->status = 0;
}
