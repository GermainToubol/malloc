/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 19:07:47 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/25 19:07:47 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
 * @file ft_strchr.c
 */

#include <stddef.h>
#include <stdint.h>

#include <libft.h>

#define LOW 0x0101010101010101L
#define HIGH 0x8080808080808080L

/**
 * @fn char *ft_strchr(const char *s, int c)
 * @param s: the string
 * @param c: the searched character as an unsigned char.
 * @return the position of the first matching character, or NULL if not found.
 */
static uint32_t	ft_has_zeros(uint64_t s)
{
	return (!((s - LOW) & ~s & HIGH));
}

char	*ft_strchr(const char *s, int c)
{
	const uint64_t	*s64 = (const uint64_t *)s;
	uint64_t		c64;

	c64 = LOW * c;
	while (ft_has_zeros(*s64) && ft_has_zeros(*s64 ^ c64))
		++s64;
	s = (const char *)s64;
	while (1)
	{
		if (*s == c)
			return ((char *)s);
		if (!*s)
			return (NULL);
		++s;
	}
}
