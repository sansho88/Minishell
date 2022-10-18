/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:46:34 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/18 17:37:10 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	rm_heredoc(void)
{
	static int	nb_heredoc = 0;
	char		*tmp;

	tmp = ft_new_heredocname(&nb_heredoc);
	while (access(tmp, R_OK) == 0)
	{
		unlink(tmp);
		free(tmp);
		tmp = ft_new_heredocname(&nb_heredoc);
	}
	free(tmp);
}

void	pwd_set(t_args *d)
{
	int	i;

	i = 0;
	while (d->env[i])
	{
		if (ft_strncmp(d->env[i], "PWD=", 4) == 0)
		{
			free(d->env[i]);
			d->env[i] = ft_strdup("PWD=");
			d->env[i] = ft_strjoin_free(d->env[i], d->pwd, 1);
		}
		i++;
	}
}
void	data_initialize(t_args *d, int argc)
{
	char	*tmp;

	d->count = 0;
	d->argc = argc;
	d->next_mode = 0;
	d->stdin_pos = 0;
	d->stdout_pos = 0;
	d->acutal_arg = 0;
	d->j = 0;
	d->is_append = 0;
	d->append_pos = 0;
	d->heredoc_pos = 0;
	d->env_len = 0;
	d->pwd_len = 0;
	d->is_path_set = true;
	d->is_built_in = false;
	d->pid = malloc(sizeof(int) * (argc + 1));
	d->is_redirect = false;
	d->is_unset = false;
	tmp = ft_calloc(BUFFER_SIZE, sizeof(char));
	getcwd(tmp, BUFFER_SIZE);
	d->pwd = strdup(tmp);
	printf("pwd de base : %s\n\n", d->pwd);
	free(tmp);
	pwd_set(d);
	path_hub(d);
}

int	exec_home(t_argmode *argv, int argc, t_args *d)
{
	int	i;
	int	rl_stdin;

	rl_stdin = dup(0);
	i = 0;
	data_initialize(d, argc);
	sorting_hub(d, argv);
	i = 0;
	while (i < d->argc)
	{
		waitpid(d->pid[i], &errno, 0);
		i++;
	}
	free(d->pid);
	rm_heredoc();
	close(d->tube[0]);
	close(d->tube[1]);
	//free(d->pwd);
	//d->pwd = NULL;
	ft_dup2(rl_stdin, 0);
	free_all(d->path);
	return (1);
}
