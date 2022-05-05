/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:06:18 by rgeral            #+#    #+#             */
/*   Updated: 2022/05/04 18:39:21 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
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

char	**ft_split(char const *s, char c);
int		main(int argc, char *argv[], char *env[]);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, char const *s2);
size_t	ft_strlen(const char	*str);
int		ft_memcmp(const void	*po1, const void	*po2, size_t	size);
void	start_process(int *tube, int	*temp_tube, t_args *p);
void	progress_process(int *tube, int	*temp_tube);
int		child_generator(int *tube, int	*temp_tube, int i, t_args *p);
int		care_child(t_args *p, int nb, int *tube, int	*temp_tube);
char	*ft_strdup(const char *src);
void	execute(t_args *p, char **args, int nb);
int	process_pipe(t_args *d, int *tube, int *temp_tube, char	*argv[]);
void	fork_process(t_args *p, char	*argv[]);
int		ft_dup2(int a, int b);
int	ft_strcmp(const char	*first, const char	*second);

#endif