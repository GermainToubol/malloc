/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 18:51:59 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/24 18:51:59 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
 * @file ft_strlcpy.c
 */
#include <stddef.h>
#include <stdint.h>

#include <libft.h>
#define ONES 0x0101010101010101L
#define HIGH 0x8080808080808080L

/**
 * @fn size_t ft_strlcpy(char *dest, const char *src, size_t size)
 * @param dest: destination buffer
 * @param src: initial string
 * @param size: size of dest
 * @return length of the initial string
 */
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t			i;
	uint64_t		*d;
	const uint64_t	*s;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	d = (uint64_t *)dest;
	s = (const uint64_t *)src;
	while (i < (size >> 3) && !((*s - ONES) & ~*s & HIGH))
	{
		*d++ = *s++;
		++i;
	}
	i <<= 3;
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		++i;
	}
	if (i == size)
		i = size - 1;
	dest[i] = '\0';
	return (ft_strlen(src));
}
