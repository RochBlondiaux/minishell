/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:41 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/20 21:03:51 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_app	*app;

	app = load_application();
		// error(readline(ft_strjoin(GREEN, PROMPT_SYMBOL)));
	unload_application(app);
	return (EXIT_SUCCESS);
}
