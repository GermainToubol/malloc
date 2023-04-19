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

#include <stddef.h>
#include <stdint.h>

#define M64(x) (x & 63)
#define D64(x) (x >> 6)

/**
 * @fn void ft_tiny_free(t_tiny *block, void *addr)
 */
void ft_tiny_free(t_tiny *block, void *addr) {
    if (addr == NULL || block == NULL)
        return;
    uint64_t offset;

    offset = (uintptr_t)addr - (uintptr_t)block->data;
    if (offset % TINY_DATA_SIZE != 0)
        return;
    offset /= TINY_DATA_SIZE;
    if (offset >= N_TINYS)
        return;
    if (block->table[0] == 0 && block->table[1] == 0)
        ft_queue_push(&g_master.qtiny, &block->node);
    block->table[D64(offset)] |= ((uint64_t)1 << M64(offset));
}
