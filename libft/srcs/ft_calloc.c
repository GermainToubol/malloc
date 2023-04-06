/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:47:10 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/12 14:30:37 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new;

	if (nmemb && size && (size_t)-1 / size < nmemb)
		return (NULL);
	new = malloc(nmemb * size);
	if (new)
		ft_bzero(new, nmemb * size);
	return (new);
}
