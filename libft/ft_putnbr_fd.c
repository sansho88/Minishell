/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:09:15 by tgriffit          #+#    #+#             */
/*   Updated: 2021/11/22 11:02:57 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Écrit l’integer ’n’ sur le file descriptor donné.
 * @param n = L’integer à écrire.
 * @param fd = Le file descriptor sur lequel écrire.
 */
void	ft_putnbr_fd(int n, int fd)
{
	if (n < -2147483647)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	n %= 10;
	ft_putchar_fd((char)(n + '0'), fd);
}
