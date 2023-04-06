/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:01:57 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/23 19:01:57 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
 * @file ft_memset.c
 */
#include <stddef.h>
#include <stdint.h>

#include <libft.h>

/**
 * @fn void *ft_memset(void *s, int c, size_t n)
 * @param s: the memory buffer
 * @param c: the filling content, interpreted as an unsigned char
 * @param n: the size of the buffer
 * @return pointer to memory area s
 *
 * Fill the starting and ending bytes and align to the 8-bytes offset
 * then fill 8-bytes at time.
 */
void	*ft_memset(void *s, int c, size_t n)
{
	size_t		i;
	uint8_t		*buffer;
	uint64_t	fill;

	fill = (uint64_t)-1 / 255 * c;
	buffer = (uint8_t *)s;
	i = 0;
	while (i < n && i < 8)
	{
		buffer[i] = c;
		buffer[n - 1 - i] = c;
		++i;
	}
	if (n <= 16)
		return (s);
	while ((uintptr_t)buffer & 7)
	{
		++buffer;
		--n;
	}
	n >>= 3;
	i = 0;
	while (i < n)
		((uint64_t *)buffer)[i++] = fill;
	return (s);
}
