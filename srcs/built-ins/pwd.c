/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:39:00 by tgriffit          #+#    #+#             */
/*   Updated: 2022/06/07 18:19:09 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*pwd(char *stored_path)
{
	if (getcwd(stored_path, ft_strlen(stored_path)))
		return (stored_path);
	else
	{
		strerror(err)
		return (NULL);
	}
}
