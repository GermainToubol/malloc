/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tiny_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:57:40 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/18 21:57:40 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_tiny_init.c
 */

#include "ft_heap.h"
#include "ft_malloc.h"
#include "ft_tiny.h"
#include "libft.h"

#include <stddef.h>
#include <stdint.h>

/**
 * @fn void ft_tiny_init(t_tiny *chunk)
 * @param chunk: new t_tiny structure
 */
void ft_tiny_init(t_tiny *chunk) {
    if (chunk == NULL)
        return;
    ft_bzero(&chunk->node, sizeof(chunk->node));
    chunk->table[0] = TINY_MASK_A;
    chunk->table[1] = TINY_MASK_B;
    ft_queue_push(&g_master.qtiny, &chunk->node);
}
