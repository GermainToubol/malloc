/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:27:48 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/25 11:27:48 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
 * @file ft_strlcat.c
 */

#include <stddef.h>
#include <stdint.h>

#include <libft.h>

/**
 * @fn size_t ft_strlcat char *dest, const char *src, size_t size)
 * @param dest: destination buffer
 * @param src: source string
 * @param size: length of the buffer
 */
size_t	ft_strlcat(char *d, const char *s, size_t size)
{
	size_t	n;

	n = ft_strlen(d);
	if (n >= size)
		return (size + ft_strlen(s));
	return (n + ft_strlcpy(d + n, s, size - n));
}
