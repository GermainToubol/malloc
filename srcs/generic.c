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

#ifdef BONUS
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

__attribute__((__visibility__("default"))) void *malloc(size_t size) {
    void *addr;

#ifdef BONUS
    pthread_mutex_lock(&g_mutex);
#endif
    addr = ft_malloc(size);
#ifdef BONUS
    pthread_mutex_unlock(&g_mutex);
#endif
    return (addr);
}

__attribute__((__visibility__("default"))) void free(void *addr) {
#ifdef BONUS
    pthread_mutex_lock(&g_mutex);
#endif
    ft_free(addr);
#ifdef BONUS
    pthread_mutex_unlock(&g_mutex);
#endif
}

__attribute__((__visibility__("default"))) void *realloc(void * addr,
                                                         size_t size) {
    void *new;

#ifdef BONUS
    pthread_mutex_lock(&g_mutex);
    show_historics("realloc.start", addr, size);
#endif
    new = ft_realloc(addr, size);

#ifdef BONUS
	show_historics("realloc.end", new, size);
	pthread_mutex_unlock(&g_mutex);
#endif
    return (new);
}
