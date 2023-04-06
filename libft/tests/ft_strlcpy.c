/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:09:08 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/24 19:09:08 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <bsd/string.h>
#include <libft.h>

static int	correctness(void)
{
	char	init[4096];
	char	buffer[4096];
	char	other[4096];

	int	i = 0;
	memset(init, 'a', 4096);
	init[25] = '\0';
	while (i < 50)
	{
		if (ft_strlcpy(buffer, init, i) != strlcpy(other, init, i)
			|| strcmp(buffer, other))
		{
			printf("strlcpy: KO [%d] [%s] [%s]\n", i, buffer, other);
			return (1);
		}
		++i;
	}
	return (0);
}

static int	getdelay(size_t (*f)(char *, const char *, size_t))
{
	struct timeval	start;
	struct timeval	end;
	char			buffer[4096];
	char			dest[4096];

	memset(buffer, 'a', 4096);
	buffer[4091] = '\0';
	gettimeofday(&start, NULL);
	for (int j = 0; j < 100000; ++j)
	{
		(*f)(dest, buffer, 4096);
	}
	gettimeofday(&end, NULL);
	end.tv_sec -= start.tv_sec;
	return (1000000 * end.tv_sec + end.tv_usec - start.tv_usec);
}

static void	timecmp(void)
{
	int	std;
	int	ft;

	std = getdelay(strlcpy);
	ft = getdelay(ft_strlcpy);
	printf(" ft: %d us std: %d us %+.2f%%\n", ft, std, (ft - std)/ (float)std * 100.0);
}


int	main(void)
{
	if (correctness())
	{
		return (1);
	}
	printf("strlcpy: OK");
	timecmp();
	return (0);
}
