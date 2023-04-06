/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:33:50 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/22 22:33:50 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <libft.h>

static int	correctness(void)
{
	char	cases[][55] = {
		"0",
		"+a",
		"-a",
		"   \t 12",
		"-235",
		"2147483647",
		"-2147483647",
		"-2147483648",
		"+23q23"
	};

	size_t	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		if (atoi(cases[i]) != ft_atoi(cases[i]))
		{
			printf("atoi: KO in: %s std:[%d] ft:[%d]\n", cases[i],
				   atoi(cases[i]), ft_atoi(cases[i]));
			return (1);
		}
		++i;
	}
	return (0);
}

int	main(void)
{
		if (correctness())
	{
		return (1);
	}
	puts("atoi: OK");
	return (0);
}
