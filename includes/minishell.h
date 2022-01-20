/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/20 21:55:51 by rblondia         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>

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
typedef struct s_app {
	char	*path;
	int		running;
}			t_app;

/**
 * Commands functions
 */
void	m_cd(t_app *app, char **args);
void	m_echo(char **args);
void	m_env(char **args);
void	m_export(char **args);
void	m_pwd(t_app *app, char **args);
void	m_unset(char **args);
void	m_exit(t_app *app, char **args);
int		hande_command(t_app *app, char *name, char **args);

/**
 * Engine functions
 */
void	launch_engine_loop(t_app *app);

/**
 * Application functions
 */
t_app	*load_application(void);
void	unload_application(t_app *app);
void	start_application(t_app *app);

/**
 * Utils functions
 */
void	error(char *a);
void	info(char *a);
size_t	array_length(char **a);
void	free_array(char **a);
char	*working_directory(void);

#endif