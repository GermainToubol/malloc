/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:34:35 by gtoubol           #+#    #+#             */
/*   Updated: 2023/02/13 14:34:35 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include <libft.h>

static int	correctness(void)
{
	char	buffer[4096];

	int	i = 0;
	memset(buffer, 'a', 4096);
	strcpy(buffer, "azertyuiopqsdfghjklmwxcvbncccwcqs");
	buffer[0] = '\0';
	while (i < 30)
	{
		buffer[i] = 'a';
		buffer[++i] = '\0';
		if ((ptrdiff_t)ft_memchr(buffer, '\0', 2048) != (ptrdiff_t)memchr(buffer, '\0', 2048))
        {
            dprintf(2, "i: %d ft: %p std: %p\n", i, ft_memchr(buffer, '\0', 2048), memchr(buffer, '\0', 2048));
			return (1);
        }
	}
	return (0);
}

static int	getdelay(void *(*f)(const void *, int, size_t))
{
	struct timeval	start;
	struct timeval	end;
	char			buffer[8192];

	memset(buffer, 'a', 8192);
	buffer[8191] = '\0';
	buffer[4753] = 'c';
	gettimeofday(&start, NULL);
	for (int j = 0; j < 100000; ++j)
	{
		(*f)(buffer, 'c', 8000);
	}
	gettimeofday(&end, NULL);
	end.tv_sec -= start.tv_sec;
	return (1000000 * end.tv_sec + end.tv_usec - start.tv_usec);
}

static void	timecmp(void)
{
	int	std;
	int	ft;

	std = getdelay(memchr);
	ft = getdelay(ft_memchr);
	printf(" ft: %d us std: %d us %+.2f%%\n", ft, std, (ft - std)/ (float)std * 100.0);
}

int	main(void)
{
	if (correctness())
	{
		puts("memchr: KO");
		return (1);
	}
	printf("memchr: OK");
	timecmp();
	return (0);
}
