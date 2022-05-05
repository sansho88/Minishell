/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nigga-tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:08:12 by tgriffit          #+#    #+#             */
/*   Updated: 2022/05/05 14:29:46 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

/*
 * Trouver le PATH dans les variables ENV
 * @param env
 * @return
 *//*
char	**path(char	**env)
{
	int		i;
	int		j;
	char	**result;
	char	*temp;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_memcmp(env[i], "PATH=", 5) == 0)
		{
			result = ft_split(&env[i][5], ':');
			while (result[j])
			{
				temp = result[j];
				result[j] = ft_strjoin(result[j], "/");
				free(temp);
				j++;
			}
			return (result);
		}
		i++;
	}
	return (NULL);
}

*//*
 * Check des paths
 * @param p
 * @param args
 * @param nb
 *//*
void	execute(t_args *p, char **args, int nb)
{
	char	*tmp;
	int		j;

	j = 0;
	*//*
		Vérifie tout les path + fonction et check si c'est executable, si oui, execute, "sinon invalid path"
		ex : bin/ls
	*//*
	while (p->path[j])
	{
		tmp = ft_strjoin(p->path[j], args[0]);
		if (access(tmp, F_OK | X_OK) == 0)
			break ;
		j++;
	}
	if (access(tmp, F_OK | X_OK) != 0 && nb < p->argc - 1)
	{
		perror("Invalid Path");
		exit(EXIT_FAILURE);
	}
	else if (tmp)
	{
		args[0] = tmp;
		execve(args[0], args, p->env);
	}
}*/

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

bool	is_cmdline_ok(char *cmdline)
{
	if (!are_quotes_closed(cmdline))
		return (false);
	if (is_chars_partouze(cmdline))
	{
		printf("Chars partouze\n");
		return (false);
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
	if (is_cmdline_ok(cmd))
		return (cmd_split);
	while (*nb_args > 0)
		free(cmd_split[*(--nb_args)]);
	return (NULL);
}

int	main(void)
{
	char		*commandline;
	char		**cmd_parsed;
	int			nb_args;
	const char	*prompt = "\033[1;32mConchito \033[93m✗\033[0m ";

	commandline = ft_strdup("empty");
	while (ft_strncmp(commandline, "exit", 5))
	{
		free(commandline);
		commandline = readline(prompt);
		add_history(commandline);
		rl_redisplay();
		cmd_parsed = parse_command_line(commandline, &nb_args);
		free(cmd_parsed);
		printf("nb args entered = %d\n", nb_args);
	}
	free(commandline);
	rl_clear_history();
	exit(0);
}
