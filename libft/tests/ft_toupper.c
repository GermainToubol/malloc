/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 01:41:34 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/23 01:41:34 by gtoubol          ###   ########.fr       */
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
		if (toupper(tests[i]) != ft_toupper(tests[i]))
			return (1);
		++i;
	}
	return (0);
}

int	main(void)
{
	if (correctness())
	{
		puts("toupper: KO");
		return (1);
	}
	puts("toupper: OK");
	return (0);
}
