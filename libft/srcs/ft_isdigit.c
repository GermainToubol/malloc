/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:15:56 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/20 19:15:56 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_isdigit.c
 */

#include <libft.h>

/**
 * @fn int ft_isdigit (int c)
 * @param c: the character with value of an `unsigned char` or `EOF`
 * @return 1 if c is a digit, 0 otherwise
 *
 */
int	ft_isdigit(int c)
{
	return ((unsigned)c - '0' < 10);
}
