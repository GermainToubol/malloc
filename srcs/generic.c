/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:05:13 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/21 13:05:13 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "libft.h"

#include <pthread.h>
#include <stddef.h>

static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

__attribute__((__visibility__("default"))) void *malloc(size_t size) {
    void *addr;

    pthread_mutex_lock(&g_mutex);
    addr = ft_malloc(size);
    pthread_mutex_unlock(&g_mutex);
    return (addr);
}

__attribute__((__visibility__("default"))) void free(void *addr) {
    pthread_mutex_lock(&g_mutex);
    ft_free(addr);
    pthread_mutex_unlock(&g_mutex);
}

__attribute__((__visibility__("default"))) void *realloc(void * addr,
                                                         size_t size) {
    void *new;

    pthread_mutex_lock(&g_mutex);
    new = ft_realloc(addr, size);
    pthread_mutex_unlock(&g_mutex);
    return (new);
}
