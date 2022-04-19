/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:37:01 by tgriffit          #+#    #+#             */
/*   Updated: 2022/04/19 18:01:28 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Converts the initial portion of the string pointed
 * to by str to int representation. Doesn't support multiples ' - '.
 * @param str = Number to convert to int
 * @return The string converted to an integer
 */
int	ft_atoi(const char *str)
{
	int	nb;
	int	signe;

	signe = 1;
	nb = 0;
	while ((*str >= 8 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		nb = (nb * 10) + (*str++ - '0');
	return (nb * signe);
}
