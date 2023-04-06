/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:06:55 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/20 20:06:55 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_isprint.c
 */

#include <libft.h>

/**
 * @fn int ft_isprint (int c)
 * @param c: the character with value of an `unsigned char` or `EOF`
 * @return 1 if c is printable, 0 otherwise
 *
 * get the 95 printable characters starting from space
 */
int	ft_isprint(int c)
{
	return (((unsigned)c - ' ') < 95);
}
