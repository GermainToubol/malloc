/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gdata_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:35:43 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/07 17:35:43 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_gdata_init.c
 */

#include "ft_gdata.h"
#include "ft_tree.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

t_node *g_root = NULL;

/**
 * @fn bool ft_gdata_init(t_gdata *data, size_t size)
 * @param data: new gdata area
 * @param size: size of the area
 * @return false on success, true on error
 */
bool    ft_gdata_init(t_gdata *data, size_t size) {
    if (data == NULL)
        return true;
    if (size & BLOCK_MASK)
        return (true);
    data->size = size;

    /* If block is not last, write it size on the nextblock prevsize */
    if (size != 0) {
        *(uint64_t *)(&data->data[size - sizeof(*data)]) = size;
        t_node *new;
        new = (t_node *)(&data->data[0]);
        ft_node_init(new, new->size);
        g_root = ft_tree_insert(g_root, new);
    }
    return (false);
}
