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
# include "enums.h"
# include "structures.h"
# include "../libft/libft.h"

/**
 * Booleans
 */
# define TRUE 1
# define FALSE 0

/**
 * Application
 */
t_app		*load_application(char **env);
void		start_application_loop(t_app *app);
int			runtime(t_app *app, char *input);
void		start_application(t_app *app);
void		stop_application(t_app *app);
void		handle_mode(t_app *app, char *input, char **ret);

/**
 * Modules
 */
t_token		*lexer(t_app *app, char *input, int *result);
int			syntaxer(char *input, t_token *tokens);
t_command	**parse(char *input);
void		expand(t_app *app, t_command **commands);
void		executor(t_app *app, t_command **cmds);

/**
 * Modules utils
 */
t_token		get_token(char *input, size_t i);
t_token		get_real_token(char *a);
size_t		tokens_length(t_token *tokens);
int			is_separator(char *c, size_t index);
size_t		count_commands(char *args);
char		**parse_raw_commands(char *raw);
char		*parse_redirections(t_command *command, char *raw);
char		**parse_quotes(char *raw);
void		expand_env_vars(t_app *app, t_command *cmd);
void		expand_input(t_app *app, t_command *cmd);
void		parse_cmd_tokens(t_command **cmds, char *raw);
char		*get_executable(t_app *app, char *input);
int			fork_cmd(t_app *app, t_command *cmd);
void		clear_fork(t_command *cmd);
char		**get_executable_args(t_command *cmd);

/**
 * Builtins
 */
void		dispatch_builtins(t_app *app, t_command *cmd);
void		builtin_echo(t_command *cmd);
void		builtin_cd(t_app *app, t_command *cmd);
void		builtin_pwd(t_app *app, t_command *cmd);
void		builtin_exit(t_app *app, t_command *cmd);
void		builtin_export(t_app *app, t_command *cmd);
void		builtin_unset(t_app *app, t_command *cmd);
void		builtin_env(t_app *app, t_command *cmd);

/**
 * App utils
 */
char		*get_prompt_symbol(t_app *app);
void		error(t_app *app, char *name, char *error);
void		str_error(t_app *app, char *error);
void		disable_signal(t_app *app);
void		enable_signal(t_app *app);

/**
 * Array utils
 */
size_t		array_length(char **array);
void		free_array(char **array);
char		**sub_array(char **array, size_t start, size_t length);
char		**add_array_element(char **array, char *element);
char		**empty_array(void);

/**
 * Map utils
 */
t_env		*init_env_map(char **env);
void		add_map_element(t_env **env, t_env *new);
void		free_map(t_env **env);
t_env		*create_map_element(char *entry);
t_env		*get_map_element(t_env *env, char *name);
void		remove_map_element(t_app *app, t_env **env, char *key);
void		print_sorted_map(t_env *env);
size_t		map_length(t_env *env);

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
void		write_in_file(t_app *app, char *filename,
				char *content, int append);
int			is_relative(char *path);

/**
 * String utils
 */
void		ft_strcat(char *dst, char *src);
char		*replace_str(char *sentence, char *find, char *replace);
int			strchr_separator(char *s);
void		is_in_quotes(int *quote, char c);
void		reset_str(char **original, char *replacement);
size_t		ft_contains(char *s, char c);

/**
 * Commands utils
 */
t_command	*create_command(char **args);
void		free_command(t_command *cmd);
void		free_command_map(t_command **map);
t_command	*init_command(void);
size_t		commands_length(t_command **args);

/**
 * Builtins utils
 */
int			is_builtin(t_command *cmd);

#endif