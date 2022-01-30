/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/**
 * Libraries
 */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "colors.h"
# include "settings.h"
# include "messages.h"
# include "../libft/libft.h"

/**
 * Booleans
 */
# define TRUE 1
# define FALSE 0

/**
 * Structures
 */
typedef enum e_token {
	PIPE,
	SEMICOLON,
	AMPERSAND,
	DOUBLE_AMPERSAND,
	DOUBLE_PIPE,
	NONE
}	t_token;

typedef struct s_command {
	char	*name;
	char	**args;
	char	*input_path;
	char	*output_path;
	t_token	previous_token;
	t_token	next_token;
}			t_command;

typedef struct s_app {
	char	*path;
	int		running;
	int		error;
	pid_t	sub;
}			t_app;

/**
 * Lexer
 */
char		**lexer(t_app *app, char *input, int *result);

/**
 * Parser
 */
t_command	**parse(char **args);

/**
 * Parsing utils
 */
void		parse_redirections(t_command *command);

/**
 * Arrays Utils
 */
size_t		array_length(char **array);
void		free_array(char **array);
char		**sub_array(char **array, size_t start, size_t length);

/**
 * Tokens utils
 */
void		parse_tokens(t_command **commands, char **args);

/**
 * Commands utils
 */
int			is_separator(char *a);
t_command	*create_command(char **args, char *name, int *index);
size_t		commands_length(t_command **commands);
void		free_commands(t_command **commands);

#endif