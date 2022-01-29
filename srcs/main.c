/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:41 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/20 21:35:03 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_app app;
	int		b;

	app.running = 0;
	app.error = 0;
	char **a = lexer(&app, "wc -l | cat > out.txt | echo -n | grep Makefile < test.out", &b);
	t_command **cmds = parse(a);
	/*
	int i = 0;
	while (cmds[i])
	{
		printf("Cmd name: %s\n", cmds[i]->name);
		int j = 0;
		while (cmds[i]->args[j])
		{
			printf("Arg: %s\n", cmds[i]->args[j]);
			j++;
		}
		printf("-----------\n");
		i++;
	} */
	free_commands(cmds);
}
