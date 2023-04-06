/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:51:04 by gtoubol           #+#    #+#             */
/*   Updated: 2023/02/13 12:51:04 by gtoubol          ###   ########.fr       */
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
    int		k;

    i = 0;
    while (i < 5)
    {
        j = 0;
        while (j < 5)
        {
            k = 0;
            while (k < 10) {
                if (ft_strncmp(a[i], a[j], k) != strncmp(a[i], a[j], k))
                    return (1);
                ++k;
            }
            ++j;
        }
        ++i;
    }
    return (0);
}

static int	getdelay(int (*f)(const char *, const char *, size_t))
{
	struct timeval	start;
	struct timeval	end;
	char			buffer[8192];

	memset(buffer, 'a', 8192);
	buffer[8191] = '\0';
	gettimeofday(&start, NULL);
	for (int j = 0; j < 100000; ++j)
	{
		(*f)(buffer, buffer, 8000);
	}
	gettimeofday(&end, NULL);
	end.tv_sec -= start.tv_sec;
	return (1000000 * end.tv_sec + end.tv_usec - start.tv_usec);
}

static void	timecmp(void)
{
	int	std;
	int	ft;

	std = getdelay(strncmp);
	ft = getdelay(ft_strncmp);
	printf(" ft: %d us std: %d us %+.2f%%\n", ft, std, (ft - std)/ (float)std * 100.0);
}


int	main(void)
{
    if (correctness())
    {
        puts("strncmp KO");
        return (1);
    }
    printf("strncmp OK");
    timecmp();
    return (0);
}
