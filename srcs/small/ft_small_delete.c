/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_small_delete.c                                   :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:06:21 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/19 14:06:21 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_small_delete.c
 */

#include "ft_heap.h"
#include "ft_malloc.h"
#include "ft_small.h"

#include <stddef.h>

/**
 * @fn void ft_small_deleye(t_small *chunk)
 * @param: chunk to remove
 */
void ft_small_delete(t_small *chunk) {
    if (chunk == NULL)
        return;
    ft_queue_remove_node(&g_master.qsmall, &chunk->node);
}
