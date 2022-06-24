/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:10:33 by tgriffit          #+#    #+#             */
/*   Updated: 2022/06/24 14:23:39 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES
# include "../libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

//INCLUDE EXEC (i have to make it clean)
# include <stdlib.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <termios.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

//Defines
# define NOT_REDIR 0
# define PIPE 1
# define REDIR_TO_OUT 2
# define CONCAT_TO_OUT 3
# define REDIR_TO_IN 4
# define HEREDOC 5

# define CONCHITO "\033[1;32mConchito \033[93m✗\033[0m "

//Structs PARSING
typedef struct s_argmode{
	char	*arg;
	int		mode;
}	t_argmode;

//STRUCTS EXEC
typedef struct s_arguments
{
	char	**argv;
	char	**path;
	char	**env;
	int		argc;
	pid_t	*pid;
	int		j;
	int		acutal_arg;
	int		mod;
	int		tube[2];
	int		temp_tube[2];
	int 	redir_bck;
	int		redir_fwd;
	int		count;
	int		next_mode;
	int		stdin_pos;
	int 	stdout_pos;
	bool	is_last;
}				t_args;

// FUNCTIONS PARSING
t_argmode	*split_arg_redirect(char *cmdline, int *argc);
t_argmode	*create_targmode_array(char *cmdline);
size_t		get_nb_seps(const char *cmdline);
void		clean_quotes(char *arg);
bool		are_quotes_closed(const char *cmdline);
//void	rl_clear_history(void);

//FUNCTIONS SIGNALS
void		signal_handler(int signum);
void		get_signals(void);
void		sign_chars_manager(bool turn_on_save);

//FUNCTIONS EXEC (Have to make it clean)
char	**ft_split(char const *s, char c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, char const *s2);
//size_t	ft_strlen(const char	*str);
int		ft_memcmp(const void	*po1, const void	*po2, size_t	size);
char	*ft_strdup(const char *src);
void    process_pipe(t_args *d, t_argmode *argv);
void    fork_process(t_args *d, t_argmode *argsmod);
int		ft_dup2(int a, int b);
int		ft_strcmp(const char	*first, const char	*second);
int		exec_home(t_argmode *argv, int argc, char	*env[]);

//REBUILD
char	**path(char	**env);
void	execute(t_args *p, char **args, int nb);
void	sorting_hub(t_args *d, t_argmode *argv);
void	fork_process(t_args *d, t_argmode *argv);

// COLORS
# define BBLU	"\033[1;34m"
# define BGREEN	"\033[1;32m"
# define BRED	"\033[1;31m"
# define BLU	"\033[0;34m"
# define GRN	"\033[0;32m"
# define RED	"\033[0;31m"
# define RST	"\033[0m"
# define YLW	"\033[93m"


#endif
