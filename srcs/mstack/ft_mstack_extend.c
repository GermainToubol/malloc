/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mstack_extend.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:57:19 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/07 09:57:19 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_mstack_extend.c
 * @brief extend the current mstack
 */

#include "ft_mstack.h"

#include <stddef.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>

#define MERGE_NO       0b00
#define MERGE_FORWARD  0b01
#define MERGE_BACKWARD 0b10

/**
 * @fn size_t _ft_mstack_resize(size_t size)
 * @param size: minimal size
 * @return the minimal size containing `size` bytes and multiple of pagesize
 */
static size_t _ft_mstack_resize(size_t size) {
    size_t page = getpagesize();

    if (size & (page - 1))
        return ((size + page) & ~(page - 1));
    return (size);
}

/**
 * @fn void _ft_mstack_insert(t_mstack *root, t_mstack *new)
 * @param root: root of the mstack list
 * @param new: current mstack
 */
static void _ft_mstack_insert(t_mstack *root, t_mstack *new) {
    t_mstack *prev = NULL;

    while (root != NULL) {
        if ((uintptr_t)root < (uintptr_t) new) {
            break;
        }
        prev = root;
        root = root->next;
    }
    new->next     = root;
    new->previous = prev;
    if (prev != NULL) {
        prev->next = new;
    }
    if (root != NULL) {
        root->previous = new;
    }
}

/**
 * @fn uint8_t _ft_mstack_merge(t_mstack *new)
 * @param new: fresh new mstack
 * @return type of merge
 */
static uint8_t _ft_mstack_merge(t_mstack *new) {
    uint8_t merge = MERGE_NO;

    if (new->next != NULL
        && (new->size == (uintptr_t) new - (uintptr_t) new->next)) {
        new->size += new->next->size;
        new->next = new->next->next;
        if (new->next != NULL)
            new->next->previous = new;
        merge |= MERGE_FORWARD;
    }
    if (new->previous != NULL
        && (new->previous->size
            == (uintptr_t) new->previous - (uintptr_t) new)) {
        new->previous->size += new->size;
        new->previous->next = new->next;
        if (new->next != NULL)
            new->next->previous = new->previous;
        merge |= MERGE_BACKWARD;
    }
    return (merge);
}

/**
 * @fn void *ft_mstack_extend(t_mstack *root, size_t size)
 * @param root: root of the stacks
 * @param size: requested size
 * @return pointer to the root on success, NULL otherwise
 */
t_mstack *ft_mstack_extend(t_mstack *root, size_t size) {
    t_mstack *new;
    size_t len;

    /* Create the new pages */
    len = _ft_mstack_resize(size);
    new = mmap(NULL,
               len,
               PROT_READ | PROT_WRITE,
               MAP_ANONYMOUS | MAP_PRIVATE,
               -1,
               0);

    if (new == NULL)
        return (NULL);
    new = (t_mstack *)((uint8_t *)new + len - sizeof(t_mstack));
    ft_mstack_init(new, len);
    _ft_mstack_insert(root, new);
    if ((uintptr_t)root < (uintptr_t) new)
        root = new;
    _ft_mstack_merge(new);
    return (root);
}
