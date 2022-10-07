/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:50:11 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/07 18:29:13 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*void	path(t_args *d, char	**env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	d->path = ft_calloc(1000, sizeof(char*));
	while (env[d->env_len])
		d->env_len++;
	while (env[i])
	{
		if (ft_memcmp(env[i], "PATH=", 5) == 0)
			break;
		i++;
	}
	printf("La valeur de i est : %d\n", i);
	printf("La valeur de d->env_len est : %d\n", d->env_len);
	if (i < d->env_len)
	{
		d->path = ft_split(&env[i][5], ':');
		i = 0;
		while (d->path[i])
		{
			temp = d->path[i];
			d->path[i] = ft_strjoin(d->path[i], "/");
			free(temp);
			i++;
		}
	}
	else if (i == d->env_len)
	{
		i = 0;
		if (d->path[i])
		{
			dprintf(1, "passé\n");
			while (d->path[i])
			{
				d->path[i] = ft_calloc(1, sizeof(char *));
				i++;
			}
		}
	}
	//dprintf(1, " LEN = %d\n", len);
	//dprintf(1, "valeur de i : %d\n", i);
	
	i = 0;
	j = 0;
	len = 0;
	while (env[len])
		len++;
	while (env[i])
	{
		if (ft_memcmp(env[i], "PATH=", 5) == 0)
		{
			d->path = ft_split(&env[i][5], ':');
			while (d->path[j])
			{
				temp = d->path[j];
				d->path[j] = ft_strjoin(d->path[j], "/");
				free(temp);
				j++;
			}
		}
		i++;
	}
	dprintf(1, " LEN = %d\n", len);
	dprintf(1, "valeur de i : %d\n", i);
}*/

void	path_is_set(t_args *d, int pos)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (d->env[pos][i])
	{
		if (d->env[pos][i] == ':')
			len++;
		i++;
	}
	d->path = ft_calloc(len + 1, sizeof(char**));
	d->path = ft_split(&d->env[pos][5], ':');
	i = 0;
	while (d->path[i])
	{
		d->path[i] = ft_strjoin(d->path[i], "/");
		i++;
	}
}
void	path_hub(t_args *d)
{
	int	i;

	i = 0;
	while (d->env[d->env_len])
		d->env_len++;
	while (d->env[i])
	{
		if (ft_memcmp(d->env[i], "PATH=", 5) == 0)
			break;
		i++;
	}
	if (i < d->env_len)
	{
		path_is_set(d, i);
		d->is_path_set = true;
	}
	/*else if (i == d->env_len)
	{
		i = 0;
		if (d->path[i][1] != '\0')
		{
			dprintf(1, "hello\n\n");
			while (d->path[i])
			{
				d->path[i] = ft_calloc(1000, sizeof(char *));
				i++;
			}
		}*/
		else 
		{
			d->path = ft_calloc(1, sizeof(char**));
			d->is_path_set = false;
		}
	
}