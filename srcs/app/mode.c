/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c 	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	has_close_quote(t_app *app, char *s)
{
	t_prompt_mode	mode;

	if (!s)
		return (0);
	mode = app->mode;
	return ((mode == D_QUOTE && ft_contains(s, '"') % 2 == 1)
		|| (mode == QUOTE && ft_contains(s, '\'') % 2 == 1));
}

char	*get_right_prompt(t_app *app)
{
	if (app->mode == D_QUOTE)
		return (D_QUOTE_PROMPT);
	else if (app->mode == QUOTE)
		return (QUOTE_PROMPT);
	return (DELIMIT_PROMPT);
}

static void	update_mode(t_app *app, char *input)
{
	if (!input || ft_strlen(input) == 0)
		return ;
	if (ft_contains(input, '"') == 1
		&& (ft_strchr(input, '\'') == 0
			|| ft_strchr(input, '\'') > ft_strchr(input, '"')))
		app->mode = D_QUOTE;
	else if (ft_contains(input, '\'') == 1)
		app->mode = QUOTE;
	else if (contains_del(input))
		app->mode = DELIMIT;
	else
		app->mode = NORMAL;
}

char	*get_arg(t_app *app)
{
	char	*input;
	char	*tmp;

	input = readline(get_right_prompt(app));
	tmp = ft_strdup("");
	while (!has_close_quote(app, input))
	{
		if (!input)
		{
			errno = 125;
			str_error(app, "-minishell");
			return (NULL);
		}
		tmp = ft_strjoin_properly(ft_strjoin_properly(tmp,
					input), ft_strdup("\n"));
		input = readline(get_right_prompt(app));
	}
	tmp = ft_strjoin_properly(tmp, input);
	return (tmp);
}

void	handle_mode(t_app *app, char *input, char **ret)
{
	char	*tmp;

	update_mode(app, input);
	if (app->mode == NORMAL)
		return ;
	else if (app->mode == DELIMIT)
		reset_str(ret, delimit_all(app, input, is_the_del(input)));
	else
		tmp = get_arg(app);
	app->mode = NORMAL;
	if (!tmp)
		return ;
	input = ft_strjoin_properly(input, ft_strdup("\n"));
	*ret = ft_strjoin_properly(input, tmp);
}
