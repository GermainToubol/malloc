/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_isalpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:35:40 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/20 16:35:40 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>
#include <sys/time.h>

#include <libft.h>

static int	correctness(void)
{
	int	i;

	i = 0;
	while (i < 256)
	{
		if (isalpha(i) != 1024 * ft_isalpha(i))
		{
			printf("isalpha: KO [%d] libc[%d] ft[%d]\n",
				i, isalpha(i), ft_isalpha(i));
			return (1);
		}
		++i;
	}
	return (0);
}

static int	getdelay(int (*f)(int))
{
	struct timeval	start;
	struct timeval	end;
	int				i;

	gettimeofday(&start, NULL);
	for (int j = 0; j < 100000; ++j)
	{
		i = 0;
		while (i < 256)
		{
			(*f)(i);
			i++;
		}
	}
	gettimeofday(&end, NULL);
	end.tv_sec -= start.tv_sec;
	return (1000000 * end.tv_sec + end.tv_usec - start.tv_usec);
}

static void	timecmp(void)
{
	int	std;
	int	ft;

	std = getdelay(isalpha);
	ft = getdelay(ft_isalpha);
	printf(" ft: %d us std: %d us %+.2f%%\n", ft, std, (ft - std)/ (float)std * 100.0);
}

int	main(void)
{
	if (correctness())
		return (1);
	printf("isalpha: OK");
	timecmp();
	return (0);
}
