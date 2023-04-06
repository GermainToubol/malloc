/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:27:31 by gtoubol           #+#    #+#             */
/*   Updated: 2023/02/13 12:27:31 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include <libft.h>

static int	correctness(void)
{
    char	a[5][26] = {
        "",
        "coucou",
        "coubcou",
        "cou",
        "coucoutor"
    };
    int		i;
    int 	j;

    i = 0;
    while (i < 5)
    {
        j = 0;
        while (j < 5)
        {
            if (ft_strcmp(a[i], a[j]) != strcmp(a[i], a[j]))
                return (1);
            ++j;
        }
        ++i;
    }
    return (0);
}

static int	getdelay(int (*f)(const char *, const char *))
{
	struct timeval	start;
	struct timeval	end;
	char			buffer[8192];

	memset(buffer, 'a', 8192);
	buffer[8191] = '\0';
	gettimeofday(&start, NULL);
	for (int j = 0; j < 100000; ++j)
	{
		(*f)(buffer, buffer);
	}
	gettimeofday(&end, NULL);
	end.tv_sec -= start.tv_sec;
	return (1000000 * end.tv_sec + end.tv_usec - start.tv_usec);
}

static void	timecmp(void)
{
	int	std;
	int	ft;

	std = getdelay(strcmp);
	ft = getdelay(ft_strcmp);
	printf(" ft: %d us std: %d us %+.2f%%\n", ft, std, (ft - std)/ (float)std * 100.0);
}


int	main(void)
{
    if (correctness())
    {
        puts("strcmp KO");
        return (1);
    }
    printf("strcmp OK");
    timecmp();
    return (0);
}
