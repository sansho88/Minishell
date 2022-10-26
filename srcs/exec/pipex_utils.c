/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:52:03 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/26 10:54:56 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_dup2(int a, int b)
{
	int	fd;

	fd = dup2(a, b);
	if (fd == -1)
	{
		perror("dup error");
		exit(127);
	}
	return (fd);
}

void	free_all(char **str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**argv_parsing_init(char	*arg, t_args *d)
{
	d->i_a = 1;
	d->j_args = 0;
	d->k_args = 0;
	d->parsed = ft_calloc(ft_strlen(arg) + 2, sizeof(char **));
	if (!d->parsed)
		exit(EXIT_FAILURE);
	d->parsed[0] = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
	if (!d->parsed[0])
		exit(EXIT_FAILURE);
	while (arg[d->j_args])
	{
		if (arg[d->j_args] == ' ')
		{
			d->parsed[d->i_a] = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
			if (!d->parsed[d->i_a])
				exit(EXIT_FAILURE);
			d->i_a++;
		}
		d->j_args++;
	}
	d->i_a = 0;
	d->j_args = 0;
	d->k_args = 0;
	return (d->parsed);
}

void	argv_parsing_unquote(char *arg, t_args *d)
{
	if (arg[d->i_a] == '"' || arg[d->i_a] == '\'')
	{
		d->i_a++;
		while (arg[d->i_a] && (arg[d->i_a] != '"' || arg[d->i_a] != '\''))
		{
			if (arg[d->i_a] != '"' && arg[d->i_a] != '\'')
			{
				d->parsed[d->j_args][d->k_args] = arg[d->i_a];
				d->k_args++;
			}
			if (arg[d->i_a] == '"' || arg[d->i_a] == '\'')
				break ;
			d->i_a++;
		}
	}
}

char	**argv_parsing(char *arg, t_argmode *argv, t_args *d)
{
	d->parsed = argv_parsing_init(arg, d);
	while (arg[d->i_a])
	{
		argv_parsing_unquote(arg, d);
		if (arg[d->i_a] == ' ')
		{
			d->j_args++;
			d->i_a++;
			d->k_args = 0;
		}
		else
		{
			if (arg[d->i_a] != '"' && arg[d->i_a] != '\'')
			{
				d->parsed[d->j_args][d->k_args] = arg[d->i_a];
				d->k_args++;
			}
			d->i_a++;
		}
	}
	d->parsed[d->j_args][d->k_args] = '\0';
	d->parsed[d->j_args + 1] = NULL;
	if (d->parsed[0][0] == '\0' && argv[d->acutal_arg].mode != 5)
		printf(" : command not found\n");
	return (d->parsed);
}
