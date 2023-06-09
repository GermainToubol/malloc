/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tiny_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:15:28 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/19 12:15:28 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_tiny_free.c
 */

#include "ft_heap.h"
#include "ft_malloc.h"
#include "ft_tiny.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define M64(x) (x & 63)
#define D64(x) (x >> 6)

bool ft_istiny(t_tiny *block, void *addr) {
    uint64_t offset;

    if (addr == NULL || block == NULL)
        return (false);

    offset = (uintptr_t)addr - (uintptr_t)block->data;
    if (offset % TINY_DATA_SIZE != 0)
        return (false);
    offset /= TINY_DATA_SIZE;
    if (offset >= N_TINYS)
        return (false);
    return (true);
}

/**
 * @fn void ft_tiny_free(t_tiny *block, void *addr)
 */
void ft_tiny_free(t_tiny *block, void *addr) {
    if (!ft_istiny(block, addr))
        return;
    uint64_t offset;

    offset = (uintptr_t)addr - (uintptr_t)block->data;
    offset /= TINY_DATA_SIZE;
    if (block->table[0] == 0 && block->table[1] == 0)
        ft_queue_push(&g_master.qtiny, &block->node);
    block->table[D64(offset)] |= ((uint64_t)1 << M64(offset));
}
