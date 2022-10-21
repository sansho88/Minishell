/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:10:33 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/21 15:56:43 by rgeral           ###   ########.fr       */
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
# define BUFFER_SIZE 4200
# define DBUG(VAR_TO_DEBUG) dprintf(2, "[%s]%s:%p\n"\
, __func__, VAR_TO_DEBUG, VAR_TO_DEBUG);

# define CONCHITO "[\001\033[1;32m\002Conchito \001\033[93m\002✗\001\033[0m\002]"
# define ERR_SYNTAX "Conchito: syntax error"

//Structs PARSING
typedef struct s_argmode{
	char	*arg;
	int		mode;
	char 	*pure_arg; //will stock the quotted arg
	char	**args;
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
	int		redir_bck;
	int		redir_fwd;
	int		count;
	int		next_mode;
	int		stdin_pos;
	int		stdout_pos;
	int		is_last;
	int		is_append;
	int		append_pos;
	int		redir_count;
	char	*pwd;
	int		heredoc_pos;
	char	*needle;
	char	*path_backup;
	int		pwd_len;
	int		env_len;
	bool	is_path_set;
	bool	is_built_in;
	bool	is_redirect;
	char	**sort_env;
	bool	is_unset;
	bool	is_piped;
}				t_args;

// UTILS
void		debug_t_argmode(t_argmode *args, int nb_arg);
void		free_t_argmode(t_argmode *args, size_t *nb_args);
char		*ft_strreplace(char *str, char *to_insert, int pos, \
int len_to_replace);

// FUNCTIONS PARSING
t_argmode	*create_targmode_array(char *cmdline);
size_t		get_nb_seps(const char *cmdline);
char		*clean_quotes(char *arg);
bool		are_quotes_closed(const char *cmdline);
char		*ft_heredoc(char *stop);
char		*ft_new_heredocname(int *nb_created);
void		rl_replace_line(char *str, int idk);
//void	rl_clear_history(void);

//CHECK_CMDLINE
bool		is_cmdline_ok(char **cmdline, char **env);
bool		are_args_ok(t_argmode	*args, size_t *nb_args);
int			ft_check_redir(const char *chars, const char	*cmdline);

//QUOTES
size_t		get_nb_quote(char *str, char quote);
bool		is_str_in_quotes(const char *str, \
			const char	*start, \
			const char	*end, char quote);

//UTILS
char		**init_env(char	**env);
char		*get_next_valid_sep(char *str);
char		*replace_dollars(char *cmd, char **env);
char		*ft_strstrchr(char *target, char **tab, size_t len_target);

//UTILS_CHECK_CMDLINE
bool		is_char_inquotes(const char *cmdline, const char *target);
bool		are_slashs_ok(char	*cmdline);

//UTILS_TARGMODE_ARRAY
char		**ft_split_quotes(const char *line);
int			nb_seps_lui(char **args);

//UTILS_HEREDOC
t_argmode	*replace_heredocs(t_argmode *args, size_t nb_args);

//FUNCTIONS SIGNALS
void		signal_handler(int signum);
void		get_signals(void);
void		sign_chars_manager(bool turn_on_save);

//FUNCTIONS EXEC
/*					Minishell Execution	                          */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*			Minishell Core Exec	                          */
void		process_pipe(t_args *d, t_argmode *argv);
void		fork_process(t_args *d, t_argmode *argv);
void		sorting_hub(t_args *d, t_argmode *argv);
int			unset_hub(t_argmode *args, t_args *d);
int			exec_home(t_argmode *argv, int argc, t_args *d);
void		path_hub(t_args *d);
int			set_old_path(t_args *d);
char		*resolve_path(t_args *d, char **args);
/*********************************************************/
/*			Set Redirections Core                        */
int			set_back(t_args *d, t_argmode *argv, int i, int file);
int			set_fwd(t_args *d, t_argmode *argv, int i, int file2);
int			set_append(t_args *d, t_argmode *argv, int i, int file);
int			is_built_in(t_args *d, t_argmode *argv);
int			set_heredoc(t_args *d, t_argmode *argv, int i, int file);
void		is_append_or_heredoc(t_args *d);
void		check_if_last(t_args *d, t_argmode *argv);
/*********************************************************/
/*			Pipe Redirection Core						 */
void		ft_backward(t_args *d, t_argmode *argv);
void		ft_forward(t_args *d, t_argmode *argv);
void		one_arg(t_args *d, t_argmode *argv);
void		pipe_rebuild_first(t_args *d, t_argmode *argv);
void		process_pipe_built_in(t_args *d, t_argmode *argv);
void		pipe_rebuild_else(t_args *d, t_argmode *argv);
/*********************************************************/
/*			Utils						 				 */
int			ft_dup2(int a, int b);
void		free_all(char **str);
/*********************************************************/
/*			Built-ins Core								 */
void		make_fork_built_in(t_args *d, t_argmode *argv);
void		is_piped(t_args *d, t_argmode *argv);
/*	Env Command		*/
int			env_hub(t_argmode *args, t_args *d);
int			print_env(t_args *d);
/*==================*/
/*	Cd Command		*/
int			cd_hub(t_argmode *args, t_args *d);
int			cd_args_count(char **arg);
void		cd_back_sort_pwd(t_args *d, int len, char **pwd_copy);
/*==================*/
/*	Exit Command	*/
void		ft_exit(t_args *d, t_argmode *argv);
int			exit_hub(t_args *d, t_argmode *argv);
/*==================*/
/*	Echo Command	*/
void ft_echo(char *arg, t_args *d);
int			echo_hub(char *arg, t_args *d, t_argmode *args);
/*==================*/
/*	Pwd Command		*/
int			set_pwd(t_args *d);
void		ft_pwd(void);
int			pwd_hub(t_argmode *args, t_args *d);
/*==================*/
/*	Export Command	*/
void		sort_export_tab(t_args *d);
void		sort_tab_exec(t_args *d);
int			export_hub(t_argmode *args, t_args *d);
int			is_valid(char	*arg);
int			add_value(t_args *d, char	*arg, char	**env_copy);
/*==================*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

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