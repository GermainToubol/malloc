/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:36:45 by gtoubol           #+#    #+#             */
/*   Updated: 2023/02/14 10:36:45 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <libft.h>

#define LAST 0x8000000000000000L

int64_t	ft_atoll(const char *str, int *errcode)
{
	uint64_t	result;
	int			sign;

	result = 0;
	*errcode = 1;
	sign = 1;
	while (*str && ft_isspace(*str))
		++str;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		++str;
	}
	while (*str && ft_isdigit(*str))
	{
		*errcode = 0;
		if (((LAST - (*str - '0')) / 10 - result) & LAST )
		{
			*errcode = 2;
			return (0);
		}
		result *= 10;
		result += *str - '0';
		++str;
	}
	if (*str)
	{
		*errcode = 1;
		return (0);
	}
	if (sign < 0)
	{
		return (sign * result);
	}
	if (result & LAST)
	{
		*errcode = 2;
		return (0);
	}
	return (result);
}
