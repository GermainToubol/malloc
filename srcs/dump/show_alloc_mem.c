/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:49:23 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/17 21:49:23 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file show_alloc_mem.c
 * @brief list the allocated zones
 */

#include "ft_gdata.h"
#include "ft_malloc.h"
#include "ft_mstack.h"
#include "ft_tiny.h"

#include <libft.h>
#include <stddef.h>
#include <stdint.h>

#define REAL_SIZE(x) (x->size & ~BLOCK_MASK)

static void _show_block_tiny(uint8_t *data, uint64_t *totsize) {
    t_tiny *tiny;

    tiny = (t_tiny *)data;
    for (size_t i = 0; i < N_TINYS; i++) {
        if ((tiny->table[i / 64] & ((uint64_t)1 << (i % 64))) == 0) {
            ft_printf("%p: %u bytes\n", &tiny->data[i], TINY_DATA_SIZE);
            *totsize += TINY_DATA_SIZE;
        }
    }
}

static void _show_block_small(uint8_t *data) {
    (void)data;
}

static void _show_block_other(t_gdata *gdata) {
    ft_printf("%p: %u bytes\n", gdata->data, REAL_SIZE(gdata));
}

/**
 * @fn void show_alloc_mem(void)
 */
__attribute__((__visibility__("default"))) void show_alloc_mem(void) {
    t_mstack *mstack;
    t_gdata * gdata;
    uint64_t  totsize;

    /* Go the the bottom of the mstack */
    for (mstack = g_master.mroot; mstack != NULL && mstack->next != NULL;
         mstack = mstack->next)
        ;
    totsize = 0;
    for (; mstack != NULL; mstack = mstack->previous) {
        for (gdata = (t_gdata *)((uintptr_t)mstack - mstack->size
                                 + sizeof(*mstack));
             REAL_SIZE(gdata) != 0;
             gdata = (t_gdata *)((uintptr_t)gdata + REAL_SIZE(gdata))) {

            switch ((gdata->size & BLOCK_OTHER)) {
            case (BLOCK_TINY):
                _show_block_tiny(gdata->data, &totsize);
                break;
            case (BLOCK_SMALL):
                _show_block_small(gdata->data);
                break;
            case (BLOCK_OTHER):
                _show_block_other(gdata);
                totsize += REAL_SIZE(gdata);
                break;
            default:
                break;
            }
        }
    }
    ft_printf("totsize: %u\n", totsize);
}
