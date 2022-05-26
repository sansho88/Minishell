/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:20:21 by tgriffit          #+#    #+#             */
/*   Updated: 2022/04/25 15:49:59 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_echo(char *arg)
{
	bool	n;
	char	*tmp;

	n = !ft_strncmp(arg, "-n ", 3);
	tmp = arg;
	if (ft_strnstr(arg, "-n ", 4))
		arg = ft_strnstr(tmp, "-n ", 4) + 3;
	if (n == false)
		ft_putendl_fd(arg, 1);
	else
		ft_putstr_fd(arg, 1);
}
