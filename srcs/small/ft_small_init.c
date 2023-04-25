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
#include "libft.h"

#include <stddef.h>
#include <stdint.h>

/**
 * @fn void ft_small_init(t_small *chunk)
 * @param chunk: new t_small structure
 */
void ft_small_init(t_small *chunk) {
    if (chunk == NULL)
        return;
    ft_bzero(&chunk->node, sizeof(chunk->node));
    chunk->table[0] = SMALL_MASK_A;
    chunk->table[1] = SMALL_MASK_B;
    ft_queue_push(&g_master.qsmall, &chunk->node);
}
