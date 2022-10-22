/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:48:29 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/22 16:41:26 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	debug_t_argmode(t_argmode *args, int nb_arg)
{
	int	i;

	i = 0;
	if (args == NULL)
	{
		dprintf(2, "[%s]The struct is NULL.\n", __func__);
		return ;
	}
	while (i < nb_arg)
	{
		dprintf(1, "[%s]t_argmode->arg=%s__ t_argmode->mode=%d|addr=%p\n",
			__func__, args[i].arg, args[i].mode, args->arg);
		i++;
	}
}

void	free_t_argmode(t_argmode *args, size_t *nb_args)
{
	size_t	i;

	i = 0;
	while (i < *nb_args && args && args[i].arg)
	{
		free(args[i].arg);
		free(args[i].pure_arg);
		args[i].arg = NULL;
		args[i].pure_arg = NULL;
		args[i].mode = 0;
		i++;
	}
	if (*nb_args > 0)
		free(args);
	*nb_args = 0;
}

char	*ft_strstrchr(char *target, char **tab, size_t len)
{
	int		i;
	char	**envvars;
	char	*result;

	i = 0;
	result = ft_strdup("");
	while (tab[i])
	{
		envvars = ft_split(tab[i], '=');
		if (envvars && envvars[0] && ft_strncmp(target, *envvars, len + 1) == 0)
		{
			free(envvars[0]);
			result = ft_strjoin_free(result, envvars[1], 3);
			free(envvars);
			return (result);
		}
		if (envvars && envvars[0])
			free(envvars[0]);
		if (envvars && envvars[1])
			free(envvars[1]);
		free(envvars);
		i++;
	}
	return (result);
}

char	*ft_strreplace(char *str, char *to_insert, int pos, int len_to_replace)
{
	char			*result;
	const size_t	size = ft_strlen(str) - len_to_replace \
													+ ft_strlen(to_insert) + 1;

	if (str && ft_strlen(str) == 1 && *str == '$')
		return (str);
	result = malloc(size);
	if (!result)
		return (NULL);
	(void)ft_strlcpy(result, str, pos + 1);
	if (is_str_in_quotes(str, str + pos, &str[pos + len_to_replace], '\''))
		result = ft_strjoin_free(result, str + pos, 1);
	else
	{
		(void)ft_strlcat(result + pos, to_insert, size);
		(void)ft_strlcat(result + pos + ft_strlen(to_insert), str + pos
			+ len_to_replace, size);
	}
	free(str);
	str = NULL;
	return (result);
}
