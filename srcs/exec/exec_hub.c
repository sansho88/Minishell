/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:46:34 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/12 13:51:23 by rgeral           ###   ########.fr       */
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
	d->pid = malloc(sizeof(int) * argc - 3);
	d->is_redirect = false;
	tmp = ft_calloc(42000, sizeof(char));
	getcwd(tmp, 42000);
	d->pwd = tmp;
	free(tmp);
	path_hub(d);
}

int	exec_home(t_argmode *argv, int argc, t_args *d)
{
	int	i;
	int	status;

	i = 0;
	data_initialize(d, argc);
	sorting_hub(d, argv);
	i = 0;
	while (i < d->argc)
	{
		waitpid(d->pid[i], &errno, 0);
		free(d->pid);
		i++;
	}
	rm_heredoc();
	//free_all(d->env);
	//free(d->pwd);
	free_all(d->path);
	return (1);
}
