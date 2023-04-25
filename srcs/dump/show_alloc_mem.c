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
#include "ft_small.h"
#include "ft_tiny.h"

#include <libft.h>
#include <stddef.h>
#include <stdint.h>

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

static void _show_block_small(uint8_t *data, uint64_t *totsize) {
    t_small *small;

    small = (t_small *)data;
    for (size_t i = 0; i < N_SMALLS; i++) {
        if ((small->table[i / 64] & ((uint64_t)1 << (i % 64))) == 0) {
            ft_printf("%p: %u bytes\n", &small->data[i], SMALL_DATA_SIZE);
            *totsize += SMALL_DATA_SIZE;
        }
    }
}

static void _show_block_other(t_gdata *gdata) {
    if (REAL_SIZE(gdata) > (uint32_t)-1)
        ft_printf("%p: %u%09u bytes\n",
                  gdata->data,
                  REAL_SIZE(gdata) >> 32,
                  (uint32_t)REAL_SIZE(gdata));
    else
        ft_printf("%p: %u bytes\n", gdata->data, REAL_SIZE(gdata));
}

enum e_state
{
    UNDEFINED,
    TINY,
    SMALL,
    LARGE
};

/**
 * @fn void show_alloc_mem(void)
 */
__attribute__((__visibility__("default"))) void show_alloc_mem(void) {
#ifdef BONUS
    pthread_mutex_lock(&g_mutex);
#endif
    t_mstack *   mstack;
    t_gdata *    gdata;
    uint64_t     totsize;
    enum e_state state = UNDEFINED;

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
                if (state != TINY) {
                    state = TINY;
                    ft_printf("TINY - %p\n", gdata->data);
                }
                _show_block_tiny(gdata->data, &totsize);
                break;
            case (BLOCK_SMALL):
                if (state != SMALL) {
                    state = SMALL;
                    ft_printf("SMALL - %p\n", gdata->data);
                }
                _show_block_small(gdata->data, &totsize);
                break;
            case (BLOCK_OTHER):
                if (state != LARGE) {
                    state = LARGE;
                    ft_printf("LARGE - %p\n", gdata->data);
                }
                _show_block_other(gdata);
                totsize += REAL_SIZE(gdata);
                break;
            default:
                break;
            }
        }
    }
    ft_printf("totsize: %u\n", totsize);
#ifdef BONUS
    pthread_mutex_unlock(&g_mutex);
#endif
}
