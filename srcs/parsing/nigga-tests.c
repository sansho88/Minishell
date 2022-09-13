/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nigga-tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:08:12 by tgriffit          #+#    #+#             */
/*   Updated: 2022/09/13 17:23:11 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../libft/libft.h"

bool	are_quotes_closed(const char *cmdline)
{
	size_t	nb_single_quotes;
	size_t	nb_double_quotes;
	size_t	i;

	nb_single_quotes = 0;
	nb_double_quotes = 0;
	i = 0;
	while (cmdline[i])
	{
		if (cmdline[i] == '"' && nb_single_quotes % 2 == 0)
			nb_double_quotes++;
		else if (cmdline[i] == '\'' && nb_double_quotes % 2 == 0)
			nb_single_quotes++;
		i++;
	}
	if (nb_double_quotes % 2 == 1)
		ft_putendl_fd("Double-Quotes not closed", 2);
	if (nb_single_quotes % 2 == 1)
		ft_putendl_fd("Single-Quotes not closed", 2);
	return (nb_single_quotes % 2 == 0 && nb_double_quotes % 2 == 0);
}

bool	check_chenillle_char(char *cmdline, char testchar)
{
	char	*charpos;

	charpos = ft_strchr(cmdline, testchar);
	if (charpos)
	{
		if (*(charpos + 1) == testchar || *(charpos + 2) == testchar)
		{
			ft_putendl_fd("Syntax error", 2);
			return (false);
		}
		if (testchar == '\"' && !ft_strchr(charpos + 1, testchar))
			return (false);
	}
	return (true);
}

bool	is_chars_partouze(char *cmdline)
{
	if (!check_chenillle_char(cmdline, '|'))
		return (true);
	if (ft_strchr(cmdline, '\\') && !ft_strchr(cmdline + 1, '\'')
	&& (cmdline - 1 != NULL && !ft_strchr(cmdline - 1, '\'')))
		return (true);
	if (ft_strchr(cmdline, ';') && !ft_strchr(cmdline + 1, '\'')
	&& (cmdline - 1 != NULL && !ft_strchr(cmdline - 1, '\'')))
		return (true);
	return (false);
}

bool	is_cmdline_ok(char **cmdline, char **env)
{
	char	*testcmd;

	testcmd = ft_strtrim(*cmdline, " ");
	if (!*testcmd)
	{
		free(testcmd);
		return (false);
	}
	if (!are_quotes_closed(*cmdline))
		return (false);
	if (is_chars_partouze(*cmdline))
	{
		printf("Chars partouze\n");
		return (false);
	}
	if (ft_strchr(*cmdline, '$'))
		*cmdline = replace_dollars(*cmdline, env);
	return (true);
}

bool	str_contains_redir(char *str)
{
	return (ft_strchr(str, '>') || ft_strchr(str, '<') || ft_strchr(str, '|'));
}

bool    are_args_ok(t_argmode   *args, size_t   nb_args)
{
    size_t  i;

	if (args == NULL || nb_args == 0)
		return (false);
	i = 0;
	while (i < nb_args)
	{
		if (!args[i].arg || (!ft_str_isalnum(args[i].arg)
			&& str_contains_redir(args[i].arg)))
		{
			ft_putendl_fd("Conchito: syntax error", 2);
			free_t_argmode(args, nb_args);
			return (false);
		}
		i++;
	}
	return (true);
}

void	merge_cmd_with_args(char **cmd, size_t nb_args)
{
	size_t	i_arg;

	i_arg = 0;
	while (i_arg < nb_args)
	{
		if (ft_strchr(cmd[i_arg], '\"'))
			ft_strjoin(cmd[i_arg - 1], cmd[i_arg]);
		i_arg++;
	}
}

/**
 * Parse the command-line and transforms it with the right args (atoi if needed)
 * @param cmd = The command line
 * @param nb_args = argc-like
 * @return An "argv"-like
 */
char	**parse_command_line(char *cmd, int *nb_args)
{
	char	**cmd_split;

	if (ft_strchr(cmd, '|'))
		cmd_split = ft_split_len(cmd, '|', nb_args);
	else
		cmd_split = ft_split_len(cmd, ' ', nb_args);
	/*if (is_cmdline_ok(cmd))
		return (cmd_split);*/
	while (*nb_args > 0)
		free(cmd_split[*(--nb_args)]);
	return (NULL);
}

int	main(int argc, char *argv[], char	*env[])
{
	char		*commandline;
	t_argmode	*args;
	int			nb_args;
	char		**custom_env;

	commandline = ft_strdup("empty");
	get_signals();
	custom_env = init_env(env);
	while (commandline && ft_strncmp(commandline, "exit", 5))
	{
		free(commandline);
		sign_chars_manager(false);
		commandline = readline(CONCHITO);
		sign_chars_manager(true);
		if (!commandline)
			exit(0);
		add_history(commandline);
		dprintf(2, "[%s]command line = %s\n", __func__, commandline);
		rl_redisplay();
		if (*commandline && is_cmdline_ok(&commandline, custom_env))
		{
			nb_args = (int)get_nb_seps(commandline) + 1; //forcement au moins 1 arg
			args = create_targmode_array(commandline);
			//debug_t_argmode(args, nb_args);
			if (are_args_ok(args, nb_args))
				exec_home(args, nb_args, custom_env);
		}
	}
	exit(0);
}


