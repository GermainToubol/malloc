/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 18:01:59 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/25 18:01:59 by gtoubol          ###   ########.fr       */
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
	size_t	u, v;

	int	i = 0;
	memset(init, 'a', 4096);
	init[25] = '\0';
	while (i < 80)
	{
		memcpy(buffer, init, 1024);
		memcpy(other, init, 1024);
		buffer[20] = '\0';
		other[20] = '\0';
		u = ft_strlcat(buffer, init, i);
		v = strlcat(other, init, i);
		if (u != v || strcmp(buffer, other))
		{
			printf("strlcat: KO [%d] %ld[%s] %ld[%s]\n", i, u, buffer, v, other);
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
	memset(dest, 'b', 4096);
	buffer[1024] = '\0';
	dest[1024] = '\0';
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

	std = getdelay(strlcat);
	ft = getdelay(ft_strlcat);
	printf(" ft: %d us std: %d us %+.2f%%\n", ft, std, (ft - std)/ (float)std * 100.0);
}


int	main(void)
{
	if (correctness())
	{
		return (1);
	}
	printf("strlcat: OK");
	timecmp();
	return (0);
}
