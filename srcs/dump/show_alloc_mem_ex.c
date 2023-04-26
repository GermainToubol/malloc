/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 06:34:17 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/26 06:34:17 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file show_alloc_mem_ex.c
 */

#include "ft_gdata.h"
#include "ft_malloc.h"
#include "ft_mstack.h"
#include "ft_tiny.h"
#include "libft.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

static bool isgdata_header(void *addr, t_gdata *gdata) {
	if ((uintptr_t)addr < (uintptr_t)gdata + sizeof(*gdata))
		return (true);
	return (false);
}

static bool isfree_block(void *addr, t_gdata *gdata) {
	if ((gdata->size & BLOCK_OTHER) == 0)
		return (true);
	if ((gdata->size & BLOCK_OTHER) == BLOCK_TINY) {
		t_tiny *tiny = (t_tiny *)gdata->data;
		if ((uintptr_t)tiny->data <= (uintptr_t)addr) {
			size_t i = (uintptr_t)addr - (uintptr_t)tiny->data;
			i /= sizeof(t_tiny_data);
			if ((tiny->table[i / 64] & ((uint64_t)1 << (i % 64))))
				return (true);
		}
	}
	if ((gdata->size & BLOCK_OTHER) == BLOCK_SMALL) {
		t_small *small = (t_small *)gdata->data;
		if ((uintptr_t)small->data <= (uintptr_t)addr) {
			size_t i = (uintptr_t)addr - (uintptr_t)small->data;
			i /= sizeof(t_small_data);
			if ((small->table[i / 64] & ((uint64_t)1 << (i % 64))))
				return (true);
		}
		return (false);
	}
	return (false);
}

static void
    _build_str(char *buff, uint8_t *data, t_gdata *gdata, t_mstack *mstack) {
    ft_strlcpy(buff, "%018p ", 2048);
    for (int i = 0; i < 16; i++) {
		if ((uintptr_t)gdata + REAL_SIZE(gdata) <= (uintptr_t)&data[i])
			gdata = (t_gdata *)((uintptr_t)gdata + REAL_SIZE(gdata));
		/* mstack header */
        if ((uintptr_t)&data[i] >= (uintptr_t)mstack) {
            ft_strlcat(buff, "\033[35m%02x\033[0m ", 2048);
        }
		/* gdata header */
        else if (isgdata_header(&data[i], gdata)) {
            ft_strlcat(buff, "\033[36m%02x\033[0m ", 2048);
        }
		/* free */
        else if (isfree_block(&data[i], gdata)) {
            ft_strlcat(buff, "\033[90m%02x\033[0m ", 2048);
		}
		/* Tiny header */
        else if ((gdata->size & BLOCK_OTHER) == BLOCK_TINY) {
			ft_strlcat(buff, "\033[33m%02x\033[0m ", 2048);
		}
		/* Small header */
        else if ((gdata->size & BLOCK_OTHER) == BLOCK_SMALL) {
			ft_strlcat(buff, "\033[31m%02x\033[0m ", 2048);
		}
		/* Used Normal*/
        else {
            ft_strlcat(buff, "%02x ", 2048);
        }
    }
    buff[ft_strlen(buff) - 1] = '\n';
}

/**
 * void show_alloc_mem_ex(void)
 */
__attribute__((__visibility__("default"))) void show_alloc_mem_ex(void) {
#ifdef BONUS
    pthread_mutex_lock(&g_mutex);
#endif
    t_mstack *mstack;
    char      buff[2048];

    mstack = g_master.mroot;
    if (mstack == NULL)
        return;
    for (; mstack->next != NULL; mstack = mstack->next) {}

    ft_printf("%18s *****\n", "");
    for (; mstack != NULL; mstack = mstack->previous) {
        uint8_t *data;
        size_t   i;
        t_gdata *gdata;

        data  = (uint8_t *)mstack - mstack->size + sizeof(*mstack);
        gdata = (t_gdata *)data;

        for (i = 0 ; i < mstack->size; i += 16) {
            if ((uintptr_t)&data[i] > (uintptr_t)gdata + REAL_SIZE(gdata)) {
                gdata = (t_gdata *)((uintptr_t)gdata + REAL_SIZE(gdata));
            }
            _build_str(buff, &data[i], gdata, mstack);
            ft_printf(buff,
                      &data[i],
                      data[i],
                      data[i + 1],
                      data[i + 2],
                      data[i + 3],
                      data[i + 4],
                      data[i + 5],
                      data[i + 6],
                      data[i + 7],
                      data[i + 8],
                      data[i + 9],
                      data[i + 10],
                      data[i + 11],
                      data[i + 12],
                      data[i + 13],
                      data[i + 14],
                      data[i + 15]);
        }
        ft_printf("%18s *****\n", "");
    }
#ifdef BONUS
    pthread_mutex_unlock(&g_mutex);
#endif

}
