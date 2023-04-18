/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mstack_unmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:19:25 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/17 23:19:25 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_mstack_unmap.c
 */

#include "ft_gdata.h"
#include "ft_malloc.h"
#include "ft_mstack.h"
#include "ft_tree.h"
#include "libft.h"

#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>

void ft_mstack_unmap(t_mstack *mstack) {
    t_gdata *data;
    t_gdata *next;
    size_t   size;

    if (mstack == NULL)
        return;
    data = (t_gdata *)((uintptr_t)mstack - mstack->size + sizeof(*mstack));
    if ((data->size & BLOCK_MASK) != 0)
        return;
    next = (t_gdata *)(&data->data[data->size - sizeof(*data)]);
    if (next->size == 0) {
        size   = mstack->size;
        mstack = mstack->previous;
        if (mstack == NULL)
            g_master.mroot = NULL;
        else
            mstack->next = NULL;
        g_master.sroot = ft_tree_delete(g_master.sroot, (t_node *)data->data);
        munmap(data, size);
        return;
    }
    if (data->size > (uint64_t)getpagesize()) {
        uint64_t retreive;
        retreive = (data->size / getpagesize()) * (uint64_t)getpagesize();
        if (data->size - retreive < sizeof(t_node) + sizeof(t_gdata)
            && retreive != data->size) {
            retreive -= getpagesize();
            if (retreive == 0)
                return;
        }
        g_master.sroot = ft_tree_delete(g_master.sroot, (t_node *)data->data);
        mstack->size -= retreive;
        next->prevsize -= retreive;
        munmap(data, retreive);
        if (next->prevsize == 0)
            return;
        data           = (t_gdata *)((uintptr_t)next - next->prevsize);
        data->prevsize = 0;
        data->size     = next->prevsize;
        ft_node_init((t_node *)data->data, data->size);
        g_master.sroot = ft_tree_insert(g_master.sroot, (t_node *)data->data);
    }
}
