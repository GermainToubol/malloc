/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:32:28 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/24 16:32:28 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include <libft.h>

static int	correctness(void)
{
	int	i;
	char init[4096] = "azertyuiopmlkjhgfdsqwcvbn";
	char buff[4096];
	char other[4096];

	i = 0;
	memcpy(buff, init, 4096);
	memcpy(other, init, 4096);
	while (i < 20)
	{
		memmove(buff + i, buff + 5, 13);
		ft_memmove(other + i, other + 5 , 13);
		if (memcmp(buff, other, 4096))
		{
			printf("memmove: KO [%d]\n", i);
			for (int j = 0; j < 15; ++j)
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
		(*f)(buff, src, 4000);
		(*f)(src, buff, 4000);
	}
	gettimeofday(&end, NULL);
	end.tv_sec -= start.tv_sec;
	return (1000000 * end.tv_sec + end.tv_usec - start.tv_usec);
}

static void	timecmp(void)
{
	int	std;
	int	ft;

	std = getdelay(memmove);
	ft = getdelay(ft_memmove);
	printf(" ft: %d us std: %d us %+.2f%%\n", ft, std, (ft - std)/ (float)std * 100.0);
}

int	main(void)
{
	if (correctness())
		return (1);
	printf("memmove: OK");
	timecmp();
	return (0);
}
