/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:52:11 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/24 18:35:58 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*resolve_path(t_args *d, char **args)
{
	char	*tmp;
	int		j;

	j = -1;
	while (args[++j])
	{
		if (!is_str_in_quotes(args[j], args[j], args[j], '\''))
			clean_quotes(args[j]);
	}
	j = 0;
	tmp = NULL;
	if (access(args[0], F_OK | X_OK) == 0)
		return (args[0]);
	if (d->is_path_set == true)
	{
		while (d->path && d->path[j])
		{
			tmp = ft_strjoin(d->path[j], args[0]);
			if (tmp && access(tmp, F_OK | X_OK) == 0)
				return (tmp);
			free(tmp);
			j++;
		}
	}
	return (NULL);
}
