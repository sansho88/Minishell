/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:04:52 by tgriffit          #+#    #+#             */
/*   Updated: 2022/04/19 18:05:26 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digitcnter(int nb)
{
	int	count;

	count = 1;
	while (nb > 9)
	{
		count++;
		nb /= 10;
	}
	return (count);
}

static char	*setneg(char *str, int isneg, int nbdigits)
{
	size_t	lenstr;

	lenstr = nbdigits;
	if (isneg)
	{
		while (lenstr > 0)
		{
			str[lenstr] = str[lenstr - 1];
			lenstr--;
		}
		str[0] = '-';
		str[nbdigits + 1] = 0;
	}
	else
		ft_strlcpy(str, str, ft_strlen(str) + 1);
	return (str);
}

/**
* Allocate (with malloc(3)) and returns a string which was the int passed
 * in params. Negative numbers have to be managed.
 * @param n = The integer to convert
 * @return The string which was the int passed in argument. NULL if malloc fails.
*/
char	*ft_itoa(int n)
{
	char	*res;
	int		nbchars;
	int		i;
	_Bool	isneg;

	isneg = n < 0;
	if (isneg)
	{
		if (n == INT32_MIN)
			return (ft_strdup("-2147483648"));
		n *= -1;
	}
	nbchars = digitcnter(n);
	res = malloc(nbchars + 3);
	if (!res)
		return (0);
	res[nbchars] = 0;
	i = nbchars;
	while (i > 0)
	{
		res[--i] = (char)(n % 10 + '0');
		n /= 10;
	}
	return (setneg(res, isneg, nbchars));
}
