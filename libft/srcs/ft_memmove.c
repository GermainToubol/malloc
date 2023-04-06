/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:06:41 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/24 15:06:41 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
 * @file ft_memmove.c
 */
#include <stddef.h>
#include <stdint.h>

#include <libft.h>

static void	*_ft_moveup(void *d, const void *s, size_t n);
static void	*_ft_movedown(void *d, const void *s, size_t n);

/**
 * @fn void *ft_memmove(void *d, const void *s, size_t n)
 * @param d: destination memory buffer
 * @param s: source memory buffer
 * @param n: size of the memory buffer
 * @return destination memory buffer
 */
void	*ft_memmove(void *d, const void *s, size_t n)
{
	if ((uintptr_t)d == (uintptr_t)s)
		return (d);
	if ((uintptr_t)d < (uintptr_t)s)
		return (_ft_moveup(d, s, n));
	return (_ft_movedown(d, s, n));
}

static void	*_ft_moveup(void *d, const void *s, size_t n)
{
	uint64_t		*dest;
	const uint64_t	*src;
	size_t			i;

	i = 0;
	dest = d;
	src = s;
	while (i < (n >> 3))
	{
		dest[i] = src[i];
		++i;
	}
	i = n & ~(size_t)7;
	while (i < n)
	{
		((char *)d)[i] = ((char *)s)[i];
		++i;
	}
	return (d);
}

static void	*_ft_movedown(void *d, const void *s, size_t n)
{
	uint64_t		*dest;
	const uint64_t	*src;
	size_t			i;

	i = 0;
	dest = (uint64_t *)((uintptr_t)d + n - 8);
	src = (const uint64_t *)((uintptr_t)s + n - 8);
	while (i < (n >> 3))
	{
		dest[-i] = src[-i];
		++i;
	}
	i = n & ~(size_t)7;
	while (i < n)
	{
		((char *)d)[n - 1 - i] = ((char *)s)[n - 1 - i];
		++i;
	}
	return (d);
}
