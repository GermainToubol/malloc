/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 11:57:04 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/24 11:57:04 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdint.h>

#include <libft.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	uint8_t			*d;
	const uint8_t	*s;
	size_t			i;

	i = -1;
	d = dest;
	s = src;
	while (++i < n && i < 8)
	{
		d[i] = s[i];
		d[n - 1 - i] = s[n - 1 - i];
	}
	if (n <= 16)
		return (dest);
	while ((uintptr_t)d & 7)
	{
		++s;
		++d;
		--n;
	}
	n >>= 3;
	i = -1;
	while (++i < n)
		((uint64_t *)d)[i] = ((uint64_t *)s)[i];
	return (dest);
}
