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
typedef enum s_token {
	AMPERSAND,
	PIPE,
	AND,
	OR,
	REDIRECTION,
	LITERAL,
	SEMI_COLON,
}	t_token;

typedef struct s_command {
	char	*name;
	char	**args;
	char	*input_path;
	char	*output_path;
	char	*input;
	char	*output;
	int		status;
}			t_command;

typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_app {
	int		running;
	int		exit;
	t_env	*env;
}	t_app;

/**
 * Application
 */
t_app		*load_application(char **env);
void		start_application(t_app *app);
void		stop_application(t_app *app);

/**
 * Engine
 */
void		start_engine(t_app *app);

/**
 * Lexer
 */
t_token		*lexer(t_app *app, char *input, int *result);

/**
 * App utils
 */
char		*get_prompt_symbol(t_app *app);
void		error(t_app *app, int code);
void		str_error(t_app *app, char *error);

/**
 * Array utils
 */
size_t		array_length(char **array);
void		free_array(char **array);
char		**sub_array(char **array, size_t start, size_t length);
char		**add_array_element(char **array, char *element);

/**
 * Map utils
 */
t_env		*init_env_map(char **env);
void		add_map_element(t_env **env, t_env *new);
void		free_map(t_env **env);
t_env		*create_map_element(char *entry);
t_env		*get_map_element(t_env *env, char *name);
void		remove_map_element(t_app *app, t_env **env, char *key);

/**
 * Environment utils
 */
char		*get_env(t_app *app, char *key);
char		*env_exists(t_app *app, char *key);
void		set_env(t_app *app, char *name, char *key);

/**
 * IO Utils
 */
char		*working_directory(void);
char		*home_directory(t_app *app);
int			exists(char *path);
char		*parent(char *path);
char		*path(char *raw);
char		*read_file(t_app *app, char *path);

#endif