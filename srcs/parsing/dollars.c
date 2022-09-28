/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:38:25 by tgriffit          #+#    #+#             */
/*   Updated: 2022/09/28 16:38:25 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../incs/minishell.h"

/**
 *
 * @param str Start of the part of the str to test
 * @return the pos of the end's word, or the NULL terminating char
 */
char *get_next_valid_sep(char *str)
{
	size_t  i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '?' && str[i] != '_')
			return (&str[i]);
		i++;
	}
	return (NULL);
}

char *get_env_var(char *cmd, const char *start, size_t len_to_end, char **env)
{
	char *env_var;
	char *tmp;

	env_var = "";
	tmp = ft_strstrchr((char *)start, env, len_to_end - 1);
	if (tmp && !is_str_in_quotes(cmd, start, start + len_to_end, '\''))
		env_var = tmp;
	else if (tmp)
		env_var = ft_strndup((char *)start - 1, get_next_valid_sep(start + 1) - start + 1);
	return (env_var);
}

char	*replace_dollars(char *cmdline, char **env)
{
	char	*env_var;
	char	*next_$;
	char	*next_sep;
	int 	offset;
	int 	len;

	next_$ = ft_strchr(cmdline, '$');
	while (next_$)
	{
		next_sep = get_next_valid_sep(next_$ + 1);
		offset = (int)(next_$ - cmdline);
		if (next_sep)
		{
			len = (int)(next_sep - next_$);
			env_var = get_env_var(cmdline, next_$ + 1, next_sep - next_$ - 1, env);
		}
		else
		{
			len = (int)(ft_strlen(cmdline) - offset);
			env_var = ft_strstrchr(next_$ + 1, env, ft_strlen(next_$ + 1));
		}
		cmdline = ft_strreplace(cmdline, env_var, offset, len);
		next_$ = ft_strchr(cmdline + offset + ft_strlen(env_var), '$');
	}
	return (cmdline);
}
