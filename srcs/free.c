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
#include "libft.h"

__attribute__((__visibility__("default"))) void ft_free(void *addr) {
    t_mstack *mstack;
    t_gdata * gdata;

    if (addr == NULL)
        return;
    mstack = ft_mstack_findaddr(g_master.mroot, addr);
    if (mstack == NULL)
        return;
    gdata = ft_gdata_findaddr(
        (t_gdata *)((uintptr_t)mstack - mstack->size + sizeof(*mstack)),
        addr);
    if (gdata == NULL || (uintptr_t)&gdata->data != (uintptr_t)addr)
        return;
    ft_gdata_free(gdata);
    if (mstack->next == NULL) {
        ft_mstack_unmap(mstack);
    }
}
