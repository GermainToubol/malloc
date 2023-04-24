/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_historics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:47:43 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/21 14:47:43 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "libft.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

void show_historics(const char *action, void *ptr, size_t size) {
    if (ptr == NULL)
        return;
#ifndef BONUS
    (void)action;
    (void)ptr;
    (void)size;
#else
    int         fd;
    const char *strfd = getenv("MALLOC_HISTORICS");

    if (strfd == NULL)
        return;
    fd = ft_atoi(strfd);
    if (fd < 0 || fd > 1023)
        return;
    if (size > 0xffffffffUL) {
        ft_fprintf(fd,
                   "%s %p %u%09u\n",
                   action,
                   ptr,
                   size >> 32,
                   (uint32_t)size);
        return;
    }
    ft_fprintf(fd, "%s %p %u\n", action, ptr, size);
#endif
}
