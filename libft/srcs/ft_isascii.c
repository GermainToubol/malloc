/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:58:04 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/20 19:58:04 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_isascii.c
 */

#include <libft.h>

/**
 * @fn int ft_isascii (int c)
 * @param c: the character with value of an `unsigned char` or `EOF`
 * @return 1 if c is a digit, 0 otherwise
 *
 * Test if there is a non-zero bite out of the 0-127 range (corresponding to the
 * ascii characters)
 */
int	ft_isascii(int c)
{
	return (!(c & ~0x7f));
}
