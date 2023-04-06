/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:06:07 by gtoubol           #+#    #+#             */
/*   Updated: 2023/02/13 12:06:07 by gtoubol          ###   ########.fr       */
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
		if (ft_strrchr(buffer, '\0') != strrchr(buffer, '\0'))
			return (1);
	}
	return (0);
}

static int	getdelay(char *(*f)(const char *, int))
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
		(*f)(buffer, 'c');
	}
	gettimeofday(&end, NULL);
	end.tv_sec -= start.tv_sec;
	return (1000000 * end.tv_sec + end.tv_usec - start.tv_usec);
}

static void	timecmp(void)
{
	int	std;
	int	ft;

	std = getdelay(strrchr);
	ft = getdelay(ft_strrchr);
	printf(" ft: %d us std: %d us %+.2f%%\n", ft, std, (ft - std)/ (float)std * 100.0);
}


int	main(void)
{
	if (correctness())
	{
		puts("strrchr: KO");
		return (1);
	}
	printf("strrchr: OK");
	timecmp();
	return (0);
}
