/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:38:25 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/12 18:16:27 by tgriffit         ###   ########.fr       */
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

	if (!env)
		return (ft_strdup(""));
	tmp = ft_strstrchr((char *)start, env, len_end - 1);
	if (!is_str_in_quotes(cmd, start, start + len_end, '\''))
	{
		if (start[0] == '?' && len_end == 1)
		{
			free(tmp);
			return (ft_itoa(errno));
		}
		else if (start[0] != '?' && ft_strlen(start) == 1)
		{
			free(tmp);
			return (ft_strdup(""));
		}
		else if ((tmp && ft_strlen(start) > 0))
			return (tmp);
	}
	else if (tmp)
		return (ft_strndup((char *)start - 1,
				get_next_valid_sep((char *)start + 1) - start + 1));
	return (ft_strdup(""));
}

char	*update_cmdline(char **cmd, char *env_var, int offset, int len)
{
	char	*next_d;
	char	*tmp;

	tmp = *cmd;
	free(*cmd);
	*cmd = ft_strreplace(tmp, env_var, offset, len);
	next_d = ft_strchr(*cmd + offset + ft_strlen(env_var), '$');
	free(env_var);
	return (next_d);
}

/**
 * Replace the dollars with its corresponding environment variable,
 * if found out of single quotes.
 * @param cmd = Command Line
 * @param env
 * @return
 */
char	*replace_dollars(char *cmd, char **env) //Find leaks there
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
