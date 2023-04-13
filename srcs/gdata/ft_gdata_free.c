/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gdata_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:31:25 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/11 11:31:25 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_gdata_free.c
 */

#include "ft_gdata.h"
#include "ft_tree.h"

#include <stddef.h>
#include <stdint.h>

#define BACK_MERGE    0b01
#define FORWARD_MERGE 0b10

/**
 * void _ft_gdata_merge(t_gdata *data)
 * @param data: current gdata block
 * @return merge indicator
 */
static uint8_t _ft_gdata_merge(t_gdata *data) {
    t_gdata *previous;
    t_gdata *next;
    uint64_t size;
    uint8_t  ret;

    ret  = 0;
    size = data->size & ~BLOCK_MASK;
    next = (t_gdata *)(&data->data[size - sizeof(*data)]);
    if (size != 0 && (next->size & BLOCK_MASK) == 0
        && (next->size & ~BLOCK_MASK) != 0) {
        g_root = ft_tree_delete(g_root, (t_node *)next->data);
        data->size += next->size;
        size           = data->size & ~BLOCK_MASK;
        next           = (t_gdata *)&data->data[size - sizeof(*data)];
        next->prevsize = size;
        ret |= FORWARD_MERGE;
    }

    if ((data->size & BLOCK_USED) == 0 && data->prevsize != 0) {
        previous = (t_gdata *)((uint8_t *)data - data->prevsize);
        g_root   = ft_tree_delete(g_root, (t_node *)previous->data);
        previous->size += data->size;
        size           = previous->size & ~BLOCK_MASK;
        next           = (t_gdata *)(&previous->data[size - sizeof(*data)]);
        next->prevsize = size;
        ret |= BACK_MERGE;
    }
    ft_node_init((t_node *)data->data, data->size);
    g_root = ft_tree_insert(g_root, (t_node *)data->data);
    return (ret);
}

/**
 * @fn void ft_gdata_free(t_gdata *data)
 * @param data: current data block
 */
void ft_gdata_free(t_gdata *data) {
    uint64_t size;
    t_gdata *next;

    if (data == NULL)
        return;

    data->size &= ~BLOCK_OTHER;
    size = data->size & ~BLOCK_MASK;
    if (size == 0)
        return;
    next           = (t_gdata *)&data->data[size - sizeof(*data)];
    next->prevsize = size;
    next->size &= ~BLOCK_USED;
    _ft_gdata_merge(data);
}
