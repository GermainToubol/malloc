/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:19:55 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/20 16:19:55 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/**
 * @file ft_isalpha.c
 */

/**
 * @fn int ft_isalpha (int c)
 * @param c: the charater with value of an `unsigned char` or `EOF`
 * @return 1 if c is a letter, 0 otherwise
 *
 * The input is tranformed to the corresponding lowercase like and shifted to
 * zero. You then take only the 26 first letters.
 */
int	ft_isalpha(int c)
{
	return (((unsigned)c | 32) - 'a' < 26);
}
