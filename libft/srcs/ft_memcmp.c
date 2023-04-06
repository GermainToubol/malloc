/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:13:05 by gtoubol           #+#    #+#             */
/*   Updated: 2023/02/13 15:13:05 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_memcmp.c
 */

#include <stddef.h>
#include <stdint.h>

#include <libft.h>

/**
 * @fn int ft_memcmp(const void *s1, const void *s2, size_t n)
 * @param s1: firt buffer
 * @param s2: second buffer
 * @param n: size of the buffer
 * @return lexicographic order of s1 and s2
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const uint8_t *str1 = (const uint8_t *)s1;
	const uint8_t *str2 = (const uint8_t *)s2;

	if (n == 0)
		return (0);
	while (n - 1 && *str1 == *str2)
	{
		++str1;
		++str2;
		--n;
	}
	return (*str1 - *str2);
}
