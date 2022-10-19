/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:39:00 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/19 15:58:25 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

#define BUF_SIZE 4200

void	ft_pwd(void)
{
	char	stored_path[BUF_SIZE];

	if (!getcwd(stored_path, BUF_SIZE))
	{
		strerror(8);
		return ;
	}
	printf("%s\n", stored_path);
}

int	pwd_hub(t_argmode *args, t_args *d)
{
	d->is_built_in = true;
	if (d->append_pos != 0 || d->stdout_pos != 0 || \
		args[d->acutal_arg].mode == 1)
	{
		d->is_redirect = true;
		make_fork_built_in(d, args);
		return (0);
	}
	ft_pwd();
	return (0);
}
