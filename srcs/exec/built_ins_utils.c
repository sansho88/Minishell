/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:12:52 by rgeral            #+#    #+#             */
/*   Updated: 2022/09/30 16:57:53 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**sort_tab_exec(char	**sort_tab, int len)
{
	int 	i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (sort_tab[i])
    {
        while(j < len - 1 - i)
		{
			if(strcmp(sort_tab[j], sort_tab[j+1]) > 0)
			{
				tmp = ft_calloc(ft_strlen(sort_tab[j]), sizeof(char));
				tmp = ft_strdup(sort_tab[j]);
				sort_tab[j] = sort_tab[j + 1];
				sort_tab[j + 1] = tmp;
			}
			j++;
		}
		j = 0;
        i++;
    }
	return(sort_tab);
}

void    sort_export(t_argmode *args, t_args *d)
{
    char	**sort_tab;
    int		i;
	int 	len;

	i = 0;
	while (d->env[len])
		len++;
    sort_tab = d->env;
	sort_tab = sort_tab_exec(sort_tab, len);
	i = 0;
	while (i < len)
	{
		printf("declare -x %s\n", sort_tab[i]);
		i++;
	}
}