/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:13:45 by gtoubol           #+#    #+#             */
/*   Updated: 2023/02/13 12:13:45 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_strcmp.c
 */

#include <stddef.h>
#include <stdint.h>
#include <libft.h>

/**
 * @fn int ft_strcmp(const char *s1, const char *s2)
 * @param s1: first string
 * @param s2: second string
 * @result lexical order between s1 and s2
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		++s1;
		++s2;
	}
	return (*(uint8_t *)s1 - *(uint8_t *)s2);
}
