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
	char				*name;
	char				**args;
	char				*input_path;
	char				*input;
	char				*output_path;
	char				*output;
	struct s_command	*previous;
	struct s_command	*next;
	t_token				previous_token;
	t_token				next_token;
}			t_command;

typedef struct s_native {
	t_command	*command;
	char		*name;
	char		**args;
	pid_t 		pid;
	int			exit;
	char		*output;
}				t_native;

typedef struct s_env
{
	char			*variable;
	struct s_env	*next;
}			t_env;

typedef struct s_app {
	char	*path;
	t_env	*env;
	int		running;
	int		error;
}			t_app;

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
 * System modules
 */
char		**lexer(t_app *app, char *input, int *result);
t_command	**parse(char **args);
void		expand(t_app *app, t_command **commands);
void		executor(t_app *app, t_command **commands);

/**
 * Native commands
 */
t_native *execute_native_command(t_app *app, t_command *cmd);

/**
 * Redirections
 */
char		*redirect_input(t_app *app, t_command *command);
void		redirect_output(t_command *command);

/**
 * Builtins
 */
int			dispatch_builtin(t_app *app, t_command *command);
void		builtin_cd(t_app *app, char **args);
void		builtin_echo(char **args);
void		builtin_env(char **args);
void		builtin_exit(t_app *app);
void		builtin_export(char **args);
void		builtin_unset(char **args);
void		builtin_pwd(t_app *app);

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
char		**add_array_element(char **array, char *element);

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
void		init_commands(t_command **commands);

/**
 * Outputs utils
 */
void		error(t_app *app, int code);
void		str_error(t_app *app, char *error);

/**
 * Environment utils
 */
char		*env(char *name);

/**
 * Path utils
 */
char		*working_directory(void);
char		*home_directory(void);
int			exists(char *path);
char		*parent(char *path);
char		*path(char *raw);

/**
 * Native commands utils
 */
char		*get_command_path(char *name);
void		free_native_cmd(t_native *cmd);
t_native	*create_native_cmd(t_command *command);

/**
 * File utils
 */
char		*read_file(t_app *app, char *path);

/**
 * Application utils
 */
int			set_path(t_app *app, char *a);
char		*get_prompt_symbol(t_app *app);
void		handle_ctrl(t_app *app);

t_env	*list_env(char **env);
void	free_list_env(t_env **env);

#endif