/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:38:25 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/24 13:06:20 by tgriffit         ###   ########.fr       */
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
	size_t			i;
	size_t			len;

	i = 0;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	while (i < len)
	{
		if (!ft_isalnum(str[i]) && str[i] != '?' && str[i] != '_')
			return (&str[i]);
		i++;
	}
	return (NULL);
}

/**
 * Get the environment variable from the name detected by the $
 * @param cmd = The command line
 * @param start = Target's start
 * @param len_end = The target's length
 * @param env = the strings tab of the environment variables
 * @return The environment variable
 */
char	*get_env_var(char *cmd, const char *start, size_t len_end, char **env)
{
	char	*tmp;
	char	*target;

	if (!env)
		return (ft_strdup(""));
	if (len_end == 0)
		return (ft_strdup("$"));
	if (!is_str_in_quotes(cmd, start, start + len_end, '\''))
	{
		if (start[0] == '?' && len_end == 1)
			return (ft_itoa(g_myerrno % 255));
		target = ft_strndup(start, len_end);
		tmp = ft_strstrchr(target, env, len_end);
		free(target);
		if ((tmp && ft_strlen(start) > 0))
			return (tmp);
		free(tmp);
	}
	else if (len_end)
		return (ft_strndup((char *)start - 1,
				get_next_valid_sep((char *)start + 1) - start + 1));
	return (ft_strdup(""));
}

char	*update_cmdline(char **cmd, char *env_var, int offset, int len)
{
	char			*next_d;
	char			*tmp;
	const size_t	env_var_len = ft_strlen(env_var);

	tmp = ft_strdup(*cmd);
	free(*cmd);
	*cmd = ft_strreplace(tmp, env_var, offset, len);
	next_d = ft_strchr(*cmd + offset + env_var_len, '$');
	if (len < 2)
		next_d = NULL;
	free(env_var);
	env_var = NULL;
	return (next_d);
}

/**
 * Replace the dollars with its corresponding environment variable,
 * if found out of single quotes.
 * @param cmd = Command Line
 * @param env
 * @return
 */
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
			env_var = get_env_var(cmd, next_d + 1, ft_strlen(next_d + 1), env);
		}
		next_d = update_cmdline(&cmd, env_var, offset, len);
	}
	return (cmd);
}
