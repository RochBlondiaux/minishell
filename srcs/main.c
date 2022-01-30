/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:41 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:15 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_app app;
	int		b;

	app.running = 0;
	app.error = 0;
	char **a = lexer(&app, "wc -l || cat > out.txt | cat > licence.txt Licence.MD | grep < test.out Makefile", &b);
	t_command **cmds = parse(a);
	int i = -1;
	while (cmds[++i])
	{
		printf("--------[%s]--------\n", cmds[i]->name);
		printf("Input path: %s\n", cmds[i]->input_path);
		printf("Output path: %s\n", cmds[i]->output_path);
		printf("Input pipe: %d\n", cmds[i]->input_pipe);
		printf("Output pipe: %d\n", cmds[i]->output_pipe);
		int j = -1;
		while (cmds[i]->args[++j])
			printf("%s\n", cmds[i]->args[j]);
		printf("\n\n");
	}
	free_commands(cmds);
}
