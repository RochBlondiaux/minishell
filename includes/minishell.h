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
	char 	*input;
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
 * Lexer
 */

#endif