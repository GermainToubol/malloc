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
#include "ft_small.h"
#include "ft_tiny.h"
#include "ft_tree.h"
#include "libft.h"

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

/* clang-format off */
t_root g_master = {
    .mroot = NULL,
    .sroot = NULL,
    .qtiny = {
        .head = NULL,
        .tail = NULL
    },
    .qsmall = {
        .head = NULL,
        .tail = NULL
    }
};
/* clang-format on */

static t_node *_node_from_extension(size_t size) {
    t_mstack *stack_tmp;
    stack_tmp = ft_mstack_extend(g_master.mroot, size + sizeof(t_mstack));
    if (stack_tmp == NULL) {
        return (NULL);
    }
    g_master.mroot = stack_tmp;
    return (ft_tree_search(g_master.sroot, size));
}

static void *_malloc_large(size_t size) {
    t_node * node;
    t_gdata *data;

    size -= sizeof(data->size);
    node = ft_tree_search(g_master.sroot, size);
    if (node == NULL) {
        node = _node_from_extension(size);
        if (node == NULL) {
            return (NULL);
        }
    }
    data = (t_gdata *)node - 1;
    return (ft_gdata_alloc(data, size, 3));
}

static void *_malloc_tiny(void) {
    t_tiny *tiny;

    tiny = (t_tiny *)((uintptr_t)g_master.qtiny.head);
    if (g_master.qtiny.head == NULL) {
        t_node * node;
        t_gdata *data;
        size_t   ext_size;

        ext_size = getpagesize() - sizeof(data->size);
        node     = ft_tree_search(g_master.sroot, ext_size);
        if (node == NULL) {
            node = _node_from_extension(ext_size);
            if (node == NULL) {
                return (NULL);
            }
        }
        data = (t_gdata *)node - 1;
        tiny = ft_gdata_alloc(data, ext_size, 1);
        if (tiny == NULL)
            return (NULL);
        ft_tiny_init(tiny);
    }
    return (ft_tiny_alloc((t_tiny *)g_master.qtiny.head));
}

static void *_malloc_small(void) {
    t_small *small;

    small = (t_small *)((uintptr_t)g_master.qsmall.head);
    if (g_master.qsmall.head == NULL) {
        t_node * node;
        t_gdata *data;
        size_t   ext_size;

        ext_size = 8 * getpagesize() - sizeof(data->size);
        node     = ft_tree_search(g_master.sroot, ext_size);
        if (node == NULL) {
            node = _node_from_extension(ext_size);
            if (node == NULL) {
                return (NULL);
            }
        }
        data  = (t_gdata *)node - 1;
        small = ft_gdata_alloc(data, ext_size, 2);
        if (small == NULL)
            return (NULL);
        ft_small_init(small);
    }
    return (ft_small_alloc((t_small *)g_master.qsmall.head));
}

__attribute__((__visibility__("default"))) void *ft_malloc(size_t size) {
    if ((size & 7) != 0) {
        size += 8;
        size &= ~7;
    }
    if (size == 0)
        return (NULL);
    if (size <= TINY_THRESHOLD)
        return (_malloc_tiny());
    if (size <= LARGE_THRESHOLD)
        return (_malloc_small());
    return (_malloc_large(size));
}
