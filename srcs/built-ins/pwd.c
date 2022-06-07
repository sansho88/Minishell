/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:39:00 by tgriffit          #+#    #+#             */
/*   Updated: 2022/05/31 17:31:36 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

#define BUF_SIZE 4200

void	pwd(char *stored_path)
{
	if (!getcwd(stored_path, BUF_SIZE))
	{
		strerror(8);
		return ;
	}
}

