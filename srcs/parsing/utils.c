/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:48:29 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/06 18:58:10 by tgriffit         ###   ########.fr       */
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
	dprintf(2, "t_argmode addr=%p\n", args);
	while (i < nb_arg)
	{
		dprintf(1, "[%s]t_argmode->arg=%s__ t_argmode->mode=%d|addr=%p\n",
			__func__, args[i].arg, args[i].mode, args->arg);
		i++;
	}
}

void	free_t_argmode(t_argmode *args, size_t nb_args)
{
	size_t	i;

	i = 0;
	while (i < nb_args && args && args[i].arg)
	{
		free(args[i].arg);
		args[i].arg = NULL;
		args[i].mode = 0;
		i++;
	}
}

char	*ft_strstrchr(char *target, char **tab, size_t len_target)
{
	int		i;
	char	**env_var;
	char	*result;

	i = 0;
	result = ft_strdup("");
	env_var = ft_split(tab[i], '=');
	while (tab[i] && env_var)
	{
		env_var = ft_split(tab[i], '=');
		if (env_var[0] && ft_strncmp(env_var[0], target, len_target) == 0)
		{
			free(env_var[0]);
			result = ft_strjoin_free(result, env_var[1], 3);
			free(env_var);
			return (result);
		}
		if (env_var[0] && *env_var[0])
			free(env_var[0]);
		if (env_var[1])
			free(env_var[1]);
		free(env_var);
		i++;
	}
	return (result);
}

char	*ft_strreplace(char *str, char *to_insert, int pos, int len_to_replace)
{
	char			*result;
	const size_t	size = ft_strlen(str) - len_to_replace \
													+ ft_strlen(to_insert) + 1;

	result = malloc(size);
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, pos + 1);
	if (is_envar_in_sngl_quotes(to_insert, len_to_replace + 1, true))
		ft_strjoin_free(result, str + pos, 1);
	else
	{
		ft_strlcat(result + pos, to_insert, size);
		ft_strlcat(result + pos + ft_strlen(to_insert), str + pos
			+ len_to_replace, size);
	}
	free(str);
	return (result);
}
