/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 01:34:39 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/23 01:34:39 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
 * @file ft_tolower.c
 */
#include <libft.h>

/**
 * @fn int ft_toupper(int c)
 * @param c: unsigned char or EOF to convert
 */
int	ft_tolower(int c)
{
	if (ft_isalpha(c))
		return (c | 32);
	return (c);
}
