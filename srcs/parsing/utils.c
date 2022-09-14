
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
	size_t	i;

	result = malloc(ft_strlen(dst) + ft_strlen(src) + 1);
	target = pos - dst;
	i = 0;
	ft_strlcpy(result, dst, target + 1);
	/*while (i < target)
	{
		result[i] = dst[i];
		i++;
	}*/
	ft_strlcat(result, src, ft_strlen(result) + ft_strlen(src) + 1);
	//ft_strlcat(result, dst + i + ft_strlen(src), i + ft_strlen(src) + 1);
	//result[i + ft_strlen(src)] = '\0';
	//free(dst);
	return (result);
}

char	*replace_dollars(char *cmdline, char **env)
{
	char	*env_var;
	char	*next_$; //pos of the next $ (it's just a checkpoint, DO NOT WRITE IN, but in cmdline directly)
	char	*next_sep;

	next_$ = ft_strchr(cmdline, '$');
	//env_var = ft_strstrchr(next_$ + 1, env, ft_strchr(next_$,' ') - next_$ + 1); //todo: len of target to the next ' '
	while (next_$)
	{
		next_sep = ft_strchr(next_$, ' ');
		if (next_sep)
		{
			dprintf(2, "Variable: %.*s\n", next_sep - next_$, next_$);
			env_var = ft_strstrchr(next_$ + 1, env, next_sep - next_$ - 1);
			dprintf(2, "Value: %s\n", ft_strstrchr(next_$ + 1, env, next_sep - next_$ - 1));
			cmdline = ft_insert_str(cmdline, env_var, next_$);
			next_$ = ft_strchr(next_sep + 1, '$');
		}
		else
		{
			dprintf(2, "Variable: %s\n", next_$);
			dprintf(2, "Value: %s\n", ft_strstrchr(next_$ + 1, env, ft_strlen(next_$ + 1)));
			//cmdline = ft_insert_str(cmdline, env_var, next_$);
			break ;
		}
	/*	if (!env_var || !ft_strlen(env_var))
			env_var = "";
		printf("env_var=_%s_|next_$=_%s_\n", env_var, next_$);
		cmdline = ft_insert_str(cmdline, env_var, next_$);
		if (next_$[1] != '\0')
		{
			next_$ = ft_strchr(next_$ + 1, '$' ); //fixme
			if (next_$)
			{
				env_var = ft_strstrchr(next_$, env, ft_strchr(next_$,' ') - next_$);
				//dprintf(2, "[%s]size true next_$=%p\n", __func__, ft_strchr(next_$, ' ') || ft_strchr(next_$, '\0'));
			}
		}
		else
			break; */
		/*if (next_$ == ft_strchr(next_$, '$'))
			break;*/
	}
	dprintf(2, "cmdline should be like:%s\n", cmdline);
	return (cmdline);
}
