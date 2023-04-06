/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:47:23 by gtoubol           #+#    #+#             */
/*   Updated: 2023/02/13 12:47:23 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
 * @file ft_strncmp.c
 */

#include <stddef.h>
#include <stdint.h>
#include <libft.h>

/**
 * @fn int ft_strncmp(const char *s1, const char *s2)
 * @param s1: first string
 * @param s2: second string
 * @param n: max number of compared chars
 * @result lexical order between s1 and s2
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	--n;
	while (*s1 == *s2 && *s1 && n)
	{
		++s1;
		++s2;
		--n;
	}
	return (*(uint8_t *)s1 - *(uint8_t *)s2);
}
