/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirecs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:38:42 by tgriffit          #+#    #+#             */
/*   Updated: 2022/05/12 18:01:15 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * Check if the nexts 2 chars are redirection characters, and returns the mode
 * @param cmdline = A pointer to the first char to check
 * @return The "mode" (check minishell.h)
 */
int	ft_check_redir(const char *cmdline)
{
	if (!cmdline)
		return (NOT_REDIR);
	if (*cmdline == '|' && *(cmdline + 1))
		return (PIPE);
	else if (*cmdline == '>' && *(cmdline + 1) && *(cmdline + 1) != '>')
		return (REDIR_TO_OUT);
	else if (*cmdline == '>' && *(cmdline + 1) && *(cmdline + 1) == '>')
		return (CONCAT_TO_OUT);
	else if (*cmdline == '<' && *(cmdline + 1) && *(cmdline + 1) != '<')
		return (REDIR_TO_IN);
	else if (*cmdline == '<' && *(cmdline + 1) && *(cmdline + 1) == '<')
		return (CONCAT_TO_IN);
	else
		return (NOT_REDIR);
}

size_t	get_nb_seps(const char *cmdline)
{
	size_t	i;
	size_t	nb_seps;

	i = 0;
	nb_seps = 0;
	while (cmdline[i])
		nb_seps += ft_check_redir(&cmdline[i++]) != 0;
	return (nb_seps);
}

void	ft_trim_args(t_argmode *argmode, size_t nb_args)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (i < nb_args)
	{
		dprintf(2, "[%s]old argmode[%zu]=%s%%\n", __func__ , i, argmode[i].arg);
		tmp = ft_strdup(argmode[i].arg);
		//free(argmode[i]->arg);
		argmode[i].arg = ft_strtrim(tmp, " ");
		dprintf(2, "[%s]new argmode[%zu]=%s%%\n", __func__ , i, argmode[i].arg);
		i++;
	}
}

void	end_fill_split(t_argmode	*res, int num_part, char *cmdline, int j)
{
	res[num_part].arg = ft_strtrim(cmdline + j, " ");
	res[num_part].mode = 0;
	ft_trim_args(res, num_part);
}

t_argmode	*create_targmode_array(char *cmdline)
{
	int			i;
	int			j;
	int			num_part;
	t_argmode	*res;

	i = -1;
	j = 0;
	num_part = 0;
	res = ft_calloc(sizeof(t_argmode), get_nb_seps(cmdline) + 1);
	if (!res)
		return (NULL);
	while (cmdline[++i] && num_part != get_nb_seps(cmdline))
	{
		if (ft_check_redir(&cmdline[i]) != 0)
		{
			res[num_part].arg = ft_strndup(&cmdline[j], i - j - 1);
			res[num_part++].mode = ft_check_redir(&cmdline[i]);
			j = i + (ft_check_redir(cmdline) == 3 || ft_check_redir(cmdline) == 5) + 1;
		}
		if (num_part == get_nb_seps(cmdline))
			end_fill_split(res, num_part, cmdline, j);
	}
	return (res);
}

/*
t_argmode	ft_fill_argmode_array(char *cmdline, size_t i, int argc)
{
	static char	**tmp_split;
	static int	k;
	int			tmp_splitlen;
	t_argmode	argmode_array;

	if (tmp_split == NULL)
		tmp_split = ft_split_len(cmdline, *(cmdline + i), &tmp_splitlen); //todo: split for all redir chars and only take the split[argc]
	else
		tmp_split[k] = ft_split_len(tmp_split[k], *(cmdline + i), &tmp_splitlen)[k];
	if (tmp_splitlen > 0 && ft_strchr(tmp_split[k], *(cmdline + i)))
	{
		dprintf(2, "Chocapic\n");
		argmode_array.arg = tmp_split[k];//ft_split(tmp_split[tmp_splitlen - 1], *(cmdline + i))[tmp_splitlen];
		argmode_array.mode = ft_check_redir(cmdline + i);
		return (argmode_array);
	}
	else
	{
		argmode_array.arg = ft_strtrim(tmp_split[k], " "); //the arg is split only with the last redir actually
		argmode_array.mode = ft_check_redir(cmdline + i);
	}
	//dprintf(1, "[%s]argmode_array.arg = %s_|_ argmode_array.mode = %d\n",__func__, argmode_array.arg, argmode_array.mode);
	int j = 0;
	while (j < tmp_splitlen)
	{
		dprintf(2, "split[%d] = %s_",j,tmp_split[j]);
		j++;
	}
	while (tmp_splitlen > 0)
	{
		free(tmp_split[tmp_splitlen--]);
	}
	free(tmp_split);
	return (argmode_array);
}
*/

/**
 * Take all the args and checks if each couple of chars is a redirect.
 *
 * @param cmdline = The cmdline sent by the user.
 * @param argc = Will takes the value of numbers of args between each redirect.
 * @return A t_argmode struct which contains each arg and the "mode" associated
 * (check minishell.h)
 */
