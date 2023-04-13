/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gdata_alloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:28:54 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/11 15:28:54 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_gdata_alloc.c
 */

#include "ft_gdata.h"
#include "ft_malloc.h"
#include "ft_tree.h"

#include <stddef.h>

/**
 * @fn ft_gdata_alloc(t_gdata *data, size_t size, uint8_t type)
 * @param data: base chunk
 * @param size: requested size
 * @param type: type of use of the chunk
 * @return the address of the gdata->data on success, NULL otherwise
 */
void *ft_gdata_alloc(t_gdata *data, size_t size, uint8_t type) {
    uint64_t data_size;
    uint64_t new_size;
    t_gdata *next;
    t_gdata *new;

    if (data == NULL)
        return (NULL);
    data_size = data->size & ~BLOCK_MASK;
    if ((data->size & BLOCK_OTHER) != 0
        || size > data_size - sizeof(data->size))
        return (NULL);
    g_master.sroot = ft_tree_delete(g_master.sroot, (t_node *)data->data);
    if (data_size > size + LARGE_THRESHOLD + sizeof(data->size)) {
        new_size = size + sizeof(data->size);
        if ((new_size & BLOCK_OTHER) != 0) {
            new_size += 8;
            new_size &= ~BLOCK_OTHER;
        }
        new = (t_gdata *)(&data->data[data_size - new_size - sizeof(*data)]);
        new->size     = new_size;
        new->prevsize = data_size - new_size;
        ft_node_init((t_node *)data->data, new->prevsize);
        g_master.sroot = ft_tree_insert(g_master.sroot, (t_node *)data->data);
        data_size      = new->prevsize | (data->size & BLOCK_USED);
        data->size     = data_size;
        data           = new;
    }
    data_size = data->size & ~BLOCK_MASK;
    data->size |= (type << 1);
    next = (t_gdata *)(&data->data[data_size - sizeof(*data)]);
    next->size |= BLOCK_USED;
    return (data->data);
}
