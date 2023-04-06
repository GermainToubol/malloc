/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:41:53 by gtoubol           #+#    #+#             */
/*   Updated: 2023/02/13 11:41:53 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_strrchr.c
 */

#include <stddef.h>
#include <stdint.h>

#include <libft.h>

#define LOW 0x0101010101010101L
#define HIGH 0x8080808080808080L

static uint32_t	ft_has_zeros(uint64_t s)
{
	return (!((s - LOW) & ~s & HIGH));
}

/**
 * @fn char *ft_strrchr(const char *s, int c)
 * @param s: string
 * @param c: searched match as an unsigned char.
 * @return the position of the last matchin character, or NULL if not found
 */
char	*ft_strrchr(const char *s, int c)
{
	uint64_t		c64;
	size_t			i;

	c64 = LOW * c;
	i = ft_strlen(s);
	while (i >= 4)
	{
		if (!ft_has_zeros(*(const uint64_t *)(s + i - 4) ^ c64))
			break ;
		i -= 4;
	}
	while (i > 0)
	{
		if (s[i] == c)
			return ((char *)(s + i));
		--i;
	}
	return (NULL);
}
