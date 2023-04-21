/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:10:02 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/19 19:10:02 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file realloc.c
 */

#include "ft_gdata.h"
#include "ft_malloc.h"
#include "ft_mstack.h"
#include "ft_small.h"
#include "ft_tiny.h"
#include "ft_tree.h"
#include "libft.h"

#include <stddef.h>
#include <stdint.h>

void *_realloc_tiny(t_gdata *gdata, void *addr, size_t size) {
    t_tiny *tiny;
    void *  ptr;

    tiny = (t_tiny *)gdata->data;
    if (!ft_istiny(tiny, addr))
        return (NULL);
    if (size <= TINY_THRESHOLD)
        return (addr);
    ptr = ft_malloc(size);
    if (ptr != NULL)
        ft_memcpy(ptr, addr, TINY_DATA_SIZE);
    ft_free(addr);
    return (ptr);
}

void *_realloc_small(t_gdata *gdata, void *addr, size_t size) {
    t_small *small;
    void *   ptr;

    small = (t_small *)gdata->data;
    if (!ft_issmall(small, addr))
        return (NULL);
    if (size > TINY_THRESHOLD && size <= LARGE_THRESHOLD)
        return (addr);
    ptr = ft_malloc(size);
    if (ptr != NULL)
        ft_memcpy(ptr,
                  addr,
                  size < LARGE_THRESHOLD ? TINY_DATA_SIZE : SMALL_DATA_SIZE);
    ft_free(addr);
    return (ptr);
}

void *_realloc_large(t_gdata *gdata, void *addr, size_t size) {
    void *ptr;

    if ((uintptr_t)addr != (uintptr_t)gdata->data)
        return (NULL);
    if (size <= LARGE_THRESHOLD) {
        ptr = ft_malloc(size);
        if (ptr != NULL)
            ft_memcpy(ptr,
                      addr,
                      size <= TINY_DATA_SIZE ? TINY_DATA_SIZE :
                                               SMALL_DATA_SIZE);
        ft_free(addr);
        return (ptr);
    }

    if ((size & 7) != 0) {
        size += 8;
        size &= ~7;
    }
    /* Old block can contain new one */
    if (size <= REAL_SIZE(gdata)) {
        /* Block is not splitable */
        if (REAL_SIZE(gdata) <= size + LARGE_THRESHOLD + sizeof(gdata->size))
            return (addr);

        /* Block spiltable */
        t_gdata *new;
        size_t new_size;
        new_size = size + sizeof(*new);
        new      = (t_gdata *)(&gdata->data[REAL_SIZE(gdata) - new_size
                                       - sizeof(*gdata)]);
        ft_memmove(new->data, gdata->data, size);
        new->size = new_size | BLOCK_OTHER | BLOCK_USED;
        gdata->size =
            (REAL_SIZE(gdata) - new_size) | (gdata->size & BLOCK_MASK);
        ft_free(addr);
        return (new->data);
    }

    size_t totsize;
    totsize = REAL_SIZE(gdata);
    if ((gdata->size & BLOCK_USED) == 0)
        totsize += gdata->prevsize;
    t_gdata *next = (t_gdata *)&gdata->data[REAL_SIZE(gdata) - sizeof(*gdata)];
    if ((next->size & BLOCK_OTHER) == 0)
        totsize += REAL_SIZE(next);
    if (totsize >= size - sizeof(gdata->size)) { /* No need malloc */
        t_gdata *base;
        if ((gdata->size & BLOCK_USED) == 0 && gdata->prevsize != 0) {
            base = (t_gdata *)((uintptr_t)gdata - gdata->prevsize);
            g_master.sroot =
                ft_tree_delete(g_master.sroot, (t_node *)base->data);
        }
        else
            base = gdata;
        if ((next->size & BLOCK_OTHER) == 0 && REAL_SIZE(next) != 0) {
            g_master.sroot =
                ft_tree_delete(g_master.sroot, (t_node *)next->data);
        }
        next = (t_gdata *)(&base->data[totsize - sizeof(*gdata)]);
        next->size |= BLOCK_USED;
        if (totsize > size + LARGE_THRESHOLD + sizeof(gdata->size)) {
            /* is splitable */
            t_gdata *new;
            size_t new_size;
            new_size = size + sizeof(*new);
            new = (t_gdata *)(&base->data[totsize - new_size - sizeof(*gdata)]);
            ft_memmove(new->data, gdata->data, size);
            new->size     = new_size | BLOCK_OTHER;
            new->prevsize = totsize - new_size;
            base->size    = new->prevsize | (base->size & BLOCK_USED);
            ft_node_init((t_node *)base->data, new->prevsize);
            g_master.sroot =
                ft_tree_insert(g_master.sroot, (t_node *)base->data);
            return (new->data);
        }
        ft_memmove(base->data, gdata->data, REAL_SIZE(gdata));
        base->size = totsize | BLOCK_OTHER | (base->size & BLOCK_USED);
        return (base->data);
    }
    ptr = ft_malloc(size);
    if (ptr != NULL)
        ft_memcpy(addr, ptr, REAL_SIZE(gdata) - sizeof(gdata->size));
    ft_free(addr);
    return (ptr);
}

void *ft_realloc(void *ptr, size_t size) {
    if (ptr == NULL)
        return (ft_malloc(size));
    if (size == 0) {
        ft_free(ptr);
        return (NULL);
    }

    t_mstack *mstack;
    t_gdata * gdata;

    mstack = ft_mstack_findaddr(g_master.mroot, ptr);
    if (mstack == NULL) {
        return (NULL); /* No need to free -> no found */
    }
    gdata = ft_gdata_findaddr(
        (t_gdata *)((uintptr_t)mstack - mstack->size + sizeof(*mstack)),
        ptr);
    if (gdata == NULL) {
        return (NULL);
    }
    switch (gdata->size & BLOCK_OTHER) {
    case (BLOCK_TINY):
        return (_realloc_tiny(gdata, ptr, size));
    case (BLOCK_SMALL):
        return (_realloc_small(gdata, ptr, size));
    case (BLOCK_OTHER):
        return (_realloc_large(gdata, ptr, size));
    }
    return (NULL);
}
