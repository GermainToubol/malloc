/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tiny_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:06:21 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/19 14:06:21 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_tiny_delete.c
 */

#include "ft_heap.h"
#include "ft_malloc.h"
#include "ft_tiny.h"

#include <stddef.h>

/**
 * @fn void ft_tiny_deleye(t_tiny *chunk)
 * @param: chunk to remove
 */
void ft_tiny_delete(t_tiny *chunk) {
    if (chunk == NULL)
        return;
    ft_queue_remove_node(&g_master.qtiny, &chunk->node);
}
