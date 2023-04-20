/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:05:37 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/17 09:05:37 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file free.c
 */

#include "ft_gdata.h"
#include "ft_malloc.h"
#include "ft_mstack.h"
#include "ft_small.h"
#include "ft_tiny.h"
#include "libft.h"

#include <stdint.h>

static void _free_tiny(t_mstack *mstack, t_gdata *gdata, void *addr) {
    t_tiny *tiny;

    tiny = (t_tiny *)gdata->data;
    ft_tiny_free(tiny, addr);
    if (tiny->table[0] == TINY_MASK_A && tiny->table[1] == TINY_MASK_B) {
        ft_tiny_delete(tiny);
        ft_gdata_free(gdata);
        if (mstack->next == NULL) {
            ft_mstack_unmap(mstack);
        }
    }
}

static void _free_small(t_mstack *mstack, t_gdata *gdata, void *addr) {
    t_small *small;

    small = (t_small *)gdata->data;
    ft_small_free(small, addr);
    if (small->table[0] == SMALL_MASK_A && small->table[1] == SMALL_MASK_B) {
        ft_small_delete(small);
        ft_gdata_free(gdata);
        if (mstack->next == NULL) {
            ft_mstack_unmap(mstack);
        }
    }
}

static void _free_large(t_mstack *mstack, t_gdata *gdata, void *addr) {
    if ((uintptr_t)gdata->data != (uintptr_t)addr)
        return;
    ft_gdata_free(gdata);
    if (mstack->next == NULL) {
        ft_mstack_unmap(mstack);
    }
}

__attribute__((__visibility__("default"))) void free(void *addr) {
    t_mstack *mstack;
    t_gdata * gdata;

    if (addr == NULL)
        return;
    mstack = ft_mstack_findaddr(g_master.mroot, addr);
    if (mstack == NULL) {
        return;
    }
    gdata = ft_gdata_findaddr(
        (t_gdata *)((uintptr_t)mstack - mstack->size + sizeof(*mstack)),
        addr);
    if (gdata == NULL) {
        return;
    }
    switch (gdata->size & BLOCK_OTHER) {
    case (BLOCK_TINY):
        _free_tiny(mstack, gdata, addr);
        break;
    case (BLOCK_SMALL):
        _free_small(mstack, gdata, addr);
        break;
    case (BLOCK_OTHER):
        _free_large(mstack, gdata, addr);
        break;
    }
}
