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

static char *get(t_token token)
{
	switch (token) {
		case DOUBLE_AMPERSAND:
			return ("&&");
		case AMPERSAND:
			return ("&");
		case DOUBLE_PIPE:
			return ("||");
		case PIPE:
			return ("|");
		case SEMICOLON:
			return (";");
		case NONE:
			return ("null");
	}
	return ("null");
}

int	main(void)
{
	t_app app;
	int		b;

	app.running = 0;
	app.error = 0;
	char **a = lexer(&app, "wc -l | cat > out.txt && cat > licence.txt Licence.MD || grep < test.out Makefile", &b);
	t_command **cmds = parse(a);
	int i = -1;
	while (cmds[++i])
	{
		printf("--------[%s]--------\n", cmds[i]->name);
		printf("Input path: %s\n", cmds[i]->input_path);
		printf("Output path: %s\n", cmds[i]->output_path);
		printf("Prev token: %s\n", get(cmds[i]->previous_token));
		printf("Next token: %s\n", get(cmds[i]->next_token));
		int j = -1;
		while (cmds[i]->args[++j])
			printf("%s\n", cmds[i]->args[j]);
		printf("\n\n");
	}
	free_commands(cmds);
}
