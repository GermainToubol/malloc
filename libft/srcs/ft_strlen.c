/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:16:22 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/20 20:16:22 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_strlen.c
 */

#include <stddef.h>
#include <stdint.h>
#include <limits.h>

#include <libft.h>

#define ALIGN 7
#define ONES 0x0101010101010101L  /* ((size_t)-1/UCHAR_MAX) */
#define HIGHS 0X8080808080808080L /* (ONES * (UCHAR_MAX/2+1)) */

/**
 * @fn size_t ft_strlen (char *str)
 * @param str: the null-terminated char buffer
 * @return lenght of the string
 *
 */
size_t	ft_strlen(const char *str)
{
	const unsigned long	*a;
	unsigned long int	longword;
	const char			*c_ptr;

	c_ptr = str;
	while ((const unsigned long)c_ptr & ALIGN)
	{
		if (*c_ptr == '\0')
			return (c_ptr - str);
		++c_ptr;
	}
	a = (const unsigned long *)c_ptr;
	while (1)
	{
		longword = *a++;
		if (!((longword - ONES) & ~longword & HIGHS))
			continue ;
		--a;
		c_ptr = (const char *)a;
		while (*c_ptr)
			++c_ptr;
		return (c_ptr - str);
	}
}
