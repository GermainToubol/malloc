/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:32:04 by gtoubol           #+#    #+#             */
/*   Updated: 2023/02/13 15:32:04 by gtoubol          ###   ########.fr       */
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
            for(size_t k = 0; k <= strlen(a[i]); k++)
            {
                int u = ft_memcmp(a[i], a[j], k);
                int v = memcmp(a[i], a[j], k);
                if (u != v && u * v <= 0)
                {
                    dprintf(2, "<%s> <%s> k: %zd %d %d\n", a[i], a[j], k, ft_memcmp(a[i], a[j], k), memcmp(a[i], a[j], k));
                    return (1);
                }
            }
            ++j;
        }
        ++i;
    }
    return (0);
}

static int	getdelay(int (*f)(const void *, const void *, size_t))
{
	struct timeval	start;
	struct timeval	end;
	char			buffer[8192];

	memset(buffer, 'a', 8192);
	buffer[8191] = '\0';
	gettimeofday(&start, NULL);
	for (int j = 0; j < 100000; ++j)
	{
		(*f)(buffer, buffer, 8001);
	}
	gettimeofday(&end, NULL);
	end.tv_sec -= start.tv_sec;
	return (1000000 * end.tv_sec + end.tv_usec - start.tv_usec);
}

static void	timecmp(void)
{
	int	std;
	int	ft;

	std = getdelay(memcmp);
	ft = getdelay(ft_memcmp);
	printf(" ft: %d us std: %d us %+.2f%%\n", ft, std, (ft - std)/ (float)std * 100.0);
}


int	main(void)
{
    if (correctness())
    {
        puts("memcmp KO");
        return (1);
    }
    printf("memcmp OK");
    timecmp();
    return (0);
}
