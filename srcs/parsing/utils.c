
#include "../../incs/minishell.h"

void	debug_t_argmode(t_argmode *args, int nb_arg)
{
	int	i;

	i = 0;
	if (!args || nb_arg == 0)
	{
		printf("[%s]The struct is NULL.", __func__ );
		return ;
	}
	while (i < nb_arg)
	{
		dprintf(1, "[%s]t_argmode->arg=%s__ t_argmode->mode=%d\n",__func__, args[i].arg, args[i].mode);
		i++;
	}
}

void	free_t_argmode(t_argmode *args, int nb_args)
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
