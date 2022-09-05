
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

char	*ft_strstrchr(char *target, char **tab)
{
	int		i;
	char	**env_var;
	char	*result;

	i = 0;
	result = ft_strdup("");
	while (tab[i])
	{
		env_var = ft_split(tab[i], '=');
		if (ft_strncmp(env_var[0], target, ft_strlen(target) + 1) == 0)
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

void	replace_dollars(char *cmdline, char **env)
{
	char	*env_var;
	char	*next_$; //pos of the next $ (it's just a checkpoint, DO NOT WRITE IN, but in cmdline directly)
	char	*tmp;

	tmp = NULL;
	next_$ = ft_strchr(cmdline, '$');
	while (next_$)
	{
		env_var = ft_strstrchr(next_$ + 1, env);
		cmdline = ft_new_strcpy(cmdline, env_var);
		//todo: place the converted variable at the ex $ position
		tmp = ft_strjoin(env_var, ft_strchr(next_$, ' ')); //+ ft_strlen(next_$);
		dprintf(2, "[%s]tmp=%s\n", __func__, tmp);
		ft_strlcpy(cmdline, tmp, ft_strlen(cmdline + 1));
		next_$ = ft_strchr(next_$, '$');
		dprintf(2, "next_$=%s VS env_var=%s\n", next_$, env_var);
		//free(tmp);
		tmp = NULL;
		if (next_$ == ft_strchr(next_$, '$'))
			break;
	}
	dprintf(2, "cmdline should be like:%s\n", cmdline);
}
