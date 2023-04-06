/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:33:35 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/20 19:33:35 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_isalnum.c
 */

#include <libft.h>

/**
 * @fn int ft_isalnum (int c)
 * @param c: the character with value of an `unsigned char` or `EOF`
 * @return 1 if c is a digit or a number, 0 otherwise
 *
 */
int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
