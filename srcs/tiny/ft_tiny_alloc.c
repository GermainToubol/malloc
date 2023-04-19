/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tiny_alloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:28:18 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/19 11:28:19 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_tiny_alloc.c
 */

#include "ft_heap.h"
#include "ft_malloc.h"
#include "ft_tiny.h"

#include <stddef.h>
#include <stdint.h>

#define M64(x) (x & 63)
#define D64(x) (x >> 6)

/**
 * @fn void *ft_tiny_alloc(t_tiny *block)
 * @param block: tiny chunk container
 * @return address of the new block, or NULL if none are available
 */
void *ft_tiny_alloc(t_tiny *block) {
    if (block == NULL)
        return (NULL);
    for (size_t i = 0; i < N_TINYS; i++) {
        if (block->table[D64(i)] & ((uint64_t)1 << M64(i))) {
            block->table[D64(i)] &= ~((uint64_t)1 << M64(i));
            if (block->table[0] == 0 && block->table[1] == 0)
                ft_queue_pop(&g_master.qtiny);
            return (&block->data[i]);
        }
    }
    return (NULL);
}
