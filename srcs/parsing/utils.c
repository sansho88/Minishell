/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:48:29 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/12 18:01:11 by tgriffit         ###   ########.fr       */
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
	printf("Number of args %zu\n", nb_args);
	while (i < nb_args && args && args[i].arg )
	{
		//printf("Going to free: (%s:%u)%p\n", args[i].arg, ft_strlen(args[i].arg), args[i].arg);
		//if (ft_strlen(args[i].arg) > 0)
			free(args[i].arg);
		args[i].arg = NULL;
		args[i].mode = 0;
		i++;
	}
	printf("Going to free t_argmode: %p\n", args);
	free(args);
}

char	*ft_strstrchr(char *target, char **tab, size_t len_target)
{
	int		i;
	char	**env_vars;
	char	*result;

	i = 0;
	result = ft_strdup("");
	while (tab[i] && env_vars)
	{
		env_vars = ft_split(tab[i], '=');
		if (env_vars[0] && ft_strncmp(env_vars[0], target, len_target) == 0)
		{
			free(env_vars[0]);
			result = ft_strjoin_free(result, env_vars[1], 3);
			free(env_vars);
			return (result);
		}
		//if (env_vars[0] && *env_vars[0])
			free(env_vars[0]);
		//if (env_vars[1])
			free(env_vars[1]);
		free(env_vars);
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
	(void)ft_strlcpy(result, str, pos + 1);
	if (is_envar_in_sngl_quotes(to_insert, len_to_replace + 1, true))
		result = ft_strjoin_free(result, str + pos, 1);
	else
	{
		(void)ft_strlcat(result + pos, to_insert, size);
		(void)ft_strlcat(result + pos + ft_strlen(to_insert), str + pos
			+ len_to_replace, size);
	}
	free(str);
	return (result);
}

//j'ai pas trouvé le leak mais j'ai une piste: "$A" leak le PATH pour des raisons très obscures, ça à l'air très instable