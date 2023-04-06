/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 01:37:48 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/23 01:37:48 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <ctype.h>
#include <stdio.h>

#include <libft.h>

static int	correctness(void)
{
	char	tests[] = "fefADSMLk mlQSML;kmxw\n";
	size_t	i;

	i = 0;
	while (i < sizeof(tests) / sizeof(tests[0]))
	{
		if (tolower(tests[i]) != ft_tolower(tests[i]))
			return (1);
		++i;
	}
	return (0);
}

int	main(void)
{
	if (correctness())
	{
		puts("tolower: KO");
		return (1);
	}
	puts("tolower: OK");
	return (0);
}
