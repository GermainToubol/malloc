/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_small_free.c                                     :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:15:28 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/19 12:15:28 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_small_free.c
 */

#include "ft_heap.h"
#include "ft_malloc.h"
#include "ft_small.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define M64(x) (x & 63)
#define D64(x) (x >> 6)

bool ft_issmall(t_small *block, void *addr) {
    uint64_t offset;

    if (addr == NULL || block == NULL)
        return (false);

    offset = (uintptr_t)addr - (uintptr_t)block->data;
    if (offset % SMALL_DATA_SIZE != 0)
        return (false);
    offset /= SMALL_DATA_SIZE;
    if (offset >= N_SMALLS)
        return (false);
    return (true);
}

/**
 * @fn void ft_small_free(t_small *block, void *addr)
 */
void ft_small_free(t_small *block, void *addr) {
    if (!ft_issmall(block, addr))
        return;
    uint64_t offset;

    offset = (uintptr_t)addr - (uintptr_t)block->data;
    offset /= SMALL_DATA_SIZE;
    if (block->table[0] == 0 && block->table[1] == 0)
        ft_queue_push(&g_master.qsmall, &block->node);
    block->table[D64(offset)] |= ((uint64_t)1 << M64(offset));
}
