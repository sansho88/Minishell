
#include "../../incs/minishell.h"

void	debug_t_argmode(t_argmode *args, int nb_arg)
{
	int	i;

	i = 0;
	if (args == NULL)
	{
		dprintf(2, "[%s]The struct is NULL.\n", __func__ );
		return ;
	}
	while (i < nb_arg)
	{
		dprintf(1, "[%s]t_argmode->arg=%s__ t_argmode->mode=%d\n",__func__, args[i].arg, args[i].mode);
		i++;
	}
}

void	free_t_argmode(t_argmode *args, size_t nb_args)
{
	size_t	i;

	i = 0;
	while (i < nb_args)
	{
		free(args[i].arg);
		args[i].mode = 0;
		i++;
	}
	free(args);
}

//TODO: EXPORT: cas a gerer: "a b= c=5" env = "b="" c="5" "; export = "a   b=""   c="5" "  + 'export b+=u' = b="5u"

bool    str_in_quotes(const char *str, size_t lenstr, bool is_env_var) //todo: implement somewhere
{
    if (!(str - is_env_var) || *(str - is_env_var) != '\'')
        return (false);
    return (str[lenstr] + 1 && str[lenstr] + 1 == '\'');
}

char	*ft_strstrchr(char *target, char **tab, size_t len_target)
{
	int		i;
	char	**env_var;
	char	*result;

	i = 0;
	result = ft_strdup("");
	while (tab[i])
	{
		env_var = ft_split(tab[i], '=');
		if (ft_strncmp(env_var[0], target, len_target) == 0)
		{
			free(env_var[0]);
			result = ft_strjoin_free(result, env_var[1], 3);
			free(env_var);
			return (result);
		}
		free(env_var[0]);
		free(env_var[1]);
		free(env_var);
		i++;
	}
	return (result);
}

char    *ft_strreplace(char *str, char *to_insert, int pos, int len_to_replace)
{
	char    *result;
	size_t  size;

    size = ft_strlen(str) - len_to_replace + ft_strlen(to_insert) + 1;
	result = malloc(size);
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, pos + 1);
    if (str_in_quotes(to_insert, len_to_replace + 1, true))
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
        if (!ft_isalnum(str[i]))
            return (&str[i]);
        i++;
    }
    return (NULL);
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
			env_var = ft_strstrchr(next_$ + 1, env, next_sep - next_$ - 1);
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
