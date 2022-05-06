/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:10:33 by tgriffit          #+#    #+#             */
/*   Updated: 2022/05/05 16:26:25 by rgeral           ###   ########.fr       */
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

//INCLUDE EXEC (i have to make it clean)
# include <stdlib.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

//Defines
# define NOT_REDIR 0
# define PIPE 1
# define REDIR_TO_OUT 2
# define CONCAT_TO_OUT 3
# define REDIR_TO_IN 4
# define CONCAT_TO_IN 5

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
}				t_args;

// FUNCTIONS PARSING
t_argmode	*split_arg_redirect(char *cmdline, int *argc);
//void	rl_clear_history(void);

//FUNCTIONS EXEC (Have to make it clean)
char	**ft_split(char const *s, char c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, char const *s2);
//size_t	ft_strlen(const char	*str);
int		ft_memcmp(const void	*po1, const void	*po2, size_t	size);
void	start_process(int *tube, int	*temp_tube, t_args *p);
void	progress_process(int *tube, int	*temp_tube);
int		child_generator(int *tube, int	*temp_tube, int i, t_args *p);
int		care_child(t_args *p, int nb, int *tube, int	*temp_tube);
char	*ft_strdup(const char *src);
void	execute(t_args *p, char **args, int nb);
int	process_pipe(t_args *d, int *tube, int *temp_tube, t_argmode *argv);
void    fork_process(t_args *d, t_argmode *argsmod);
int		ft_dup2(int a, int b);
int		ft_strcmp(const char	*first, const char	*second);
int		exec_home(t_argmode *argv, int argc, char	*env[]);

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