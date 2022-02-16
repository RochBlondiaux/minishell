/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_command {
	char				*name;
	char				**args;
	char				*input_path;
	char				*output_path;
	char				*input;
	char				*output;
	int					delimiter;
	int					appender;
	int					status;
	t_token				next_token;
	t_token				previous_token;
	struct s_command	*previous_cmd;
	struct s_command	*next_cmd;
	pid_t				pid;
	int					p_status;
}						t_command;

typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_app {
	int				running;
	int				exit;
	int				last_exit;
	t_prompt_mode	mode;
	t_env			*env;
}					t_app;

#endif