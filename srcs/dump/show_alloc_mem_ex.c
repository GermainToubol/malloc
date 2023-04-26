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
#include "libft.h"

#include <stddef.h>
#include <stdint.h>

static void
    _build_str(char *buff, uint8_t *data, t_gdata *gdata, t_mstack *mstack) {
    ft_strlcpy(buff, "%018p ", 2048);
    for (int i = 0; i < 16; i++) {
        if ((uintptr_t)&data[i] >= (uintptr_t)mstack) {
            ft_strlcat(buff, "\033[35m%02x\033[0m ", 2048);
        }
        else if ((uintptr_t)&data[i] < (uintptr_t)gdata + sizeof(*gdata)
                 || (uintptr_t)&data[i]
                        >= (uintptr_t)gdata + REAL_SIZE(gdata)) {
            ft_strlcat(buff, "\033[36m%02x\033[0m ", 2048);
        }
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
        i     = 0;

        for (; i < mstack->size; i += 16) {
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
}
