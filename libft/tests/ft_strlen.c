/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:20:32 by gtoubol           #+#    #+#             */
/*   Updated: 2022/12/20 20:20:32 by gtoubol          ###   ########.fr       */
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
	buffer[0] = '\0';
	while (i < 4095)
	{
		buffer[i] = 'a';
		buffer[++i] = '\0';
		if (strlen(buffer) != ft_strlen(buffer))
			return (1);
	}
	return (0);
}

static int	getdelay(size_t (*f)(const char *))
{
	struct timeval	start;
	struct timeval	end;
	char			buffer[8192];

	memset(buffer, 'a', 8192);
	buffer[8191] = '\0';
	gettimeofday(&start, NULL);
	for (int j = 0; j < 100000; ++j)
	{
		(*f)(buffer);
	}
	gettimeofday(&end, NULL);
	end.tv_sec -= start.tv_sec;
	return (1000000 * end.tv_sec + end.tv_usec - start.tv_usec);
}

static void	timecmp(void)
{
	int	std;
	int	ft;

	std = getdelay(strlen);
	ft = getdelay(ft_strlen);
	printf(" ft: %d us std: %d us %+.2f%%\n", ft, std, (ft - std)/ (float)std * 100.0);
}


int	main(void)
{
	if (correctness())
	{
		puts("strlen: KO");
		return (1);
	}
	printf("strlen: OK");
	timecmp();
	return (0);
}
