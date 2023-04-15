/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:28:13 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/13 20:28:13 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file malloc.c
 */

#include "ft_gdata.h"
#include "ft_malloc.h"
#include "ft_mstack.h"
#include "ft_tree.h"

#include <stddef.h>

t_root g_master = { .mroot = NULL, .sroot = NULL };

void * malloc(size_t size) {
    t_node * node;
    t_gdata *data;

    size += sizeof(data->size);
    if ((size & 7) != 0) {
        size += 8;
        size &= ~7;
    }
    node = ft_tree_search(g_master.sroot, size);
    if (node == NULL) {
        t_mstack *stack_tmp;
        stack_tmp = ft_mstack_extend(g_master.mroot, size + sizeof(t_mstack));
        if (stack_tmp == NULL) {
            return (NULL);
        }
        g_master.mroot = stack_tmp;
        node           = ft_tree_search(g_master.sroot, size);
        if (node == NULL) {
            return (NULL);
        }
    }
    data = (t_gdata *)node - 1;
    return (ft_gdata_alloc(data, size, BLOCK_OTHER));
}
