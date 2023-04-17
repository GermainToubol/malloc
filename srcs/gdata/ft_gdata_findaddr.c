/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gdata_findaddr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:00:32 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/15 19:00:32 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_gdata_findaddr.c
 * @brief search address in gdata blocks
 */

#include "ft_gdata.h"

#include <stdint.h>

/**
 * @fn t_gdata *ft_gdata_findaddr(t_gdata *root, void *addr)
 * @param root: root of the gdata list
 * @param addr: searched address
 * @return address of the t_gdata structure
 */
t_gdata *ft_gdata_findaddr(t_gdata *root, void *addr) {
    uint64_t size;

    if (root == NULL)
        return (NULL);
    while ((root->size & ~BLOCK_MASK) != 0) {
        size = (root->size & ~BLOCK_MASK);
        if ((uintptr_t)&root->size <= (uintptr_t)addr
            && (uintptr_t)addr < (uintptr_t)&root->size + size)
            return (root);
        root = (t_gdata *)((uintptr_t)root + size);
    }
    return (NULL);
}
