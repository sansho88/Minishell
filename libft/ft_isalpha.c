/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isalpha.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:32:05 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/24 18:44:57 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Tests for any character for which isupper(3) or islower(3) is true.
 * The value of the argument must be representable as an unsigned char or the
 * value of EOF.
 * @param c = Char to test.
 * @return 1 if char is alphabetic, else 0.
 */
int	ft_isalpha(int c)
{
	if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z'))
		return (0);
	return (1);
}
