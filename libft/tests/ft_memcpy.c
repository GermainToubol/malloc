/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:07:44 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/24 12:07:44 by gtoubol          ###   ########.fr       */
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
	char coucou[4096];

	i = 0;
	bzero(buff, 4096);
	bzero(other, 4096);
	memset(coucou, 'a', 4096);
	while (i < 256)
	{
		memcpy((void *)((unsigned long)buff + 3), coucou, i * 15);
		ft_memcpy((void *)((unsigned long)other + 3), coucou, i * 15);
		if (memcmp(buff, other, 4096))
		{
			printf("memcpy: KO [%d]\n", i);
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

static int	getdelay(void *(*f)(void *, const void *, size_t))
{
	struct timeval	start;
	struct timeval	end;
	char			buff[4096];
	char			src[4096];

	gettimeofday(&start, NULL);
	for (int j = 0; j < 100000; ++j)
	{
		(*f)(buff+3, src + 1, 4000);
	}
	gettimeofday(&end, NULL);
	end.tv_sec -= start.tv_sec;
	return (1000000 * end.tv_sec + end.tv_usec - start.tv_usec);
}

static void	timecmp(void)
{
	int	std;
	int	ft;

	std = getdelay(memcpy);
	ft = getdelay(ft_memcpy);
	printf(" ft: %d us std: %d us %+.2f%%\n", ft, std, (ft - std)/ (float)std * 100.0);
}

int	main(void)
{
	if (correctness())
		return (1);
	printf("memcpy: OK");
	timecmp();
	return (0);
}
