/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 11:41:24 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/24 11:41:24 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>
#include <libft.h>

static int	correctness(void)
{
	int	i;
	char buff[4096];
	char other[4096];

	i = 0;
	memset(buff, 0xff, 4096);
	memset(other, 0xff, 4096);
	while (i < 256)
	{
		bzero((void *)((unsigned long)buff + 3), i * 15);
		ft_bzero((void *)((unsigned long)other + 3), i * 15);
		if (memcmp(buff, other, 4096))
		{
			printf("bzero: KO [%d]\n", i);
			for (int j = 0; j < 80; ++j)
			{
				printf("%d (%lx): %d %d\n", j, (uintptr_t)(other + j) & 7, buff[j], other[j]);
			}
			return (1);
		}
		++i;
	}
	return (0);
}

static int	getdelay(void (*f)(void *, size_t))
{
	struct timeval	start;
	struct timeval	end;
	char			buff[4096];

	gettimeofday(&start, NULL);
	for (int j = 0; j < 100000; ++j)
	{
		(*f)((void *)((size_t)buff + 1), 4095);
	}
	gettimeofday(&end, NULL);
	end.tv_sec -= start.tv_sec;
	return (1000000 * end.tv_sec + end.tv_usec - start.tv_usec);
}

static void	timecmp(void)
{
	int	std;
	int	ft;

	std = getdelay(bzero);
	ft = getdelay(ft_bzero);
	printf(" ft: %d us std: %d us %+.2f%%\n", ft, std, (ft - std)/ (float)std * 100.0);
}

int	main(void)
{
	if (correctness())
		return (1);
	printf("bzero: OK");
	timecmp();
	return (0);
}
