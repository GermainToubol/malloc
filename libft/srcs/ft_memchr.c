/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:06:25 by gtoubol           #+#    #+#             */
/*   Updated: 2023/02/13 14:06:25 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_memchr.c
 */

#include <stddef.h>
#include <stdint.h>

#include <libft.h>

#define ONES 0x0101010101010101L
#define HIGH 0x8080808080808080L

static int	ft_has_zeros(uint64_t x)
{
	return (!((x - ONES) & ~x & HIGH));
}

/**
 * @fn void *ft_memchr(const void *b, int c, size_t s)
 * @param b: memory buffer
 * @param c: searched byte (as uint8_t)
 * @param s: size of the buffer
 * @return pointer to firt occurrence of c (or NULL)
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	const uint64_t	*s64 = (const uint64_t *)s;
	const uint8_t	*s8 = (const uint8_t *)s;
	const uint64_t	c64 = ONES * c;
	size_t			i;

	i = 0;
	while (ft_has_zeros(*s64 ^ c64) && i < (n >> 3))
	{
		++s64;
		++i;
	}
	i <<= 3;
	s8 = (const uint8_t *)s64;
	while (i < n)
	{
		if (*s8 == c)
			return ((void *)s8);
		++s8;
		++i;
	}
	return (NULL);
}
