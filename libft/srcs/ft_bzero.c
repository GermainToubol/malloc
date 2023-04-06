/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 11:38:09 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/24 11:38:09 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
 * @file ft_bzero.c
 */
#include <stddef.h>
#include <libft.h>

/**
 * @fn void *ft_bzero(void *s, size_t n)
 * @param s: memory buffer
 * @param n: size of the memory buffer
 */
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
