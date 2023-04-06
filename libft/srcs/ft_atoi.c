/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:47:11 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/21 14:47:11 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_atoi.c
 */

#include <limits.h>

#include <libft.h>

static int	ft_ispace(int c)
{
	if ((unsigned)c - '\b' < 6 || c == ' ')
		return (1);
	return (0);
}

/**
 * @fn int ft_atoi(const char *str)
 * @param str: the sting
 * @return the value of the first digits interpreted with their signs
 *
 * go through the negatives to be able to reach INT_MIN
 */
int	ft_atoi(const char *str)
{
	int	result;
	int	neg;

	result = 0;
	neg = 0;
	while (ft_ispace(*str))
		++str;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = 1;
		++str;
	}
	while (ft_isdigit(*str))
	{
		result = 10 * result - (*str - '0');
		++str;
	}
	if (neg)
		return (result);
	return (-result);
}
