/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:38:25 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/06 12:22:26 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../incs/minishell.h"

/**
 *
 * @param str Start of the part of the str to test
 * @return the pos of the end's word, or the NULL terminating char
 */
char	*get_next_valid_sep(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '?' && str[i] != '_')
			return (&str[i]);
		i++;
	}
	return (NULL);
}

char	*get_env_var(char *cmd, const char *start, size_t len_end, char **env)
{
	char	*env_var;
	char	*tmp;

	env_var = "";
	tmp = ft_strstrchr((char *)start, env, len_end - 1);
	if (!is_str_in_quotes(cmd, start, start + len_end, '\''))
	{
		if (start[0] == '?' && len_end == 1)
			return (ft_strdup(ft_itoa(errno)));
		else if (start[0] != '?' && ft_strlen(start) == 1)
			env_var = "";
		else if ((tmp && ft_strlen(start) > 0))
			env_var = tmp;
	}
	else if (tmp)
		env_var = ft_strndup((char *)start - 1, get_next_valid_sep(start + 1)
		- start + 1);
	return (env_var);
}

char	*replace_dollars(char *cmd, char **env)
{
	char	*env_var;
	char	*next_d;
	char	*next_sep;
	int		offset;
	int		len;

	next_d = ft_strchr(cmd, '$');
	while (next_d)
	{
		next_sep = get_next_valid_sep(next_d + 1);
		offset = (int)(next_d - cmd);
		if (next_sep)
		{
			len = (int)(next_sep - next_d);
			env_var = get_env_var(cmd, next_d + 1, next_sep - next_d - 1, env);
		}
		else
		{
			len = (int)(ft_strlen(cmd) - offset);
			env_var = get_env_var(cmd, next_d + 1, ft_strlen(next_d + 1), env);//ft_strstrchr(next_d + 1, env, ft_strlen(next_d + 1));
		}
		cmd = ft_strreplace(cmd, env_var, offset, len);
		next_d = ft_strchr(cmd + offset + ft_strlen(env_var), '$');
	}
	return (cmd);
}
