/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_small_init.c                                     :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:57:40 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/18 21:57:40 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_small_init.c
 */

#include "ft_heap.h"
#include "ft_malloc.h"
#include "ft_small.h"

#include <stddef.h>
#include <stdint.h>

/**
 * @fn void ft_small_init(t_small *chunk)
 * @param chunk: new t_small structure
 */
void ft_small_init(t_small *chunk) {
    if (chunk == NULL)
        return;
    chunk->node     = (t_heap) { NULL, NULL, NULL, NULL, NULL };
    chunk->table[0] = SMALL_MASK_A;
    chunk->table[1] = SMALL_MASK_B;
    ft_queue_push(&g_master.qsmall, &chunk->node);
}
