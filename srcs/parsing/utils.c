
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

char	*ft_new_strcpy(char *dst, char *src)
{
	char *new_copy;

	new_copy = malloc(ft_strlen(dst) + ft_strlen(src) + 1);
	ft_strlcpy(new_copy, dst, ft_strlen(dst) + ft_strlen(src) + 1);
	//free(dst);
	//dprintf(2, "[%s]new_copy=%s\n", __func__, new_copy);
	return (new_copy);
}

char *ft_insert_str(char *dst, char *src, char *pos)
{
	char 	*result;
	size_t	target;
	size_t	sz;

	sz = ft_strlen(dst) + ft_strlen(src) + 1;
	result = malloc(sz);
	target = pos - dst;
	ft_strlcpy(result, dst, target + 1);
	ft_strlcat(result, src, ft_strlen(result) + ft_strlen(src) + 1);
	ft_strlcat(result, dst + target, sz);
	//free(dst);
	return (result);
}

char    *ft_strreplace(char *str, char *newchaine, int pos, int len)
{
	char    *result;
	size_t  sz;

	sz = ft_strlen(str) - len + ft_strlen(newchaine) + 1;
	result = malloc(sz);
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, pos + 1);
	ft_strlcat(result + pos, newchaine, sz);
	ft_strlcat(result + pos + ft_strlen(newchaine), str + pos + len, sz);
	free(str);
	return (result);
}

char	*replace_dollars(char *cmdline, char **env)
{
	char	*env_var;
	char	*next_$;
	char	*next_sep;
	int 	off;
	int 	len;

	next_$ = ft_strchr(cmdline, '$');
	while (next_$)
	{
		next_sep = ft_strchr(next_$, ' ');
		off = (int)(next_$ - cmdline);
		if (next_sep)
		{
			len = (int)(next_sep - next_$);
			env_var = ft_strstrchr(next_$ + 1, env, next_sep - next_$ - 1);
		}
		else
		{
			len = (int)(ft_strlen(cmdline) - off);
			env_var = ft_strstrchr(next_$ + 1, env, ft_strlen(next_$ + 1));
		}
		cmdline = ft_strreplace(cmdline, env_var, off, len);
		next_$ = ft_strchr(cmdline + off + ft_strlen(env_var), '$');
	}
	return (cmdline);
}
