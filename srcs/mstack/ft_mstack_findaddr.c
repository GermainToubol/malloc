/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mstack_findaddr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:41:56 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/15 17:41:56 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_mstack_findaddr.c
 * @brief find the block of a given address
 */

#include "ft_mstack.h"

#include <stddef.h>
#include <stdint.h>

/**
 * @fn t_mstack *ft_mstack_findaddr(t_mstack *root, void *addr)
 * @param root: root of the ft_mstack
 * @param addr: searched address
 * @return address of the block containing the address or NULL if not found
 */
t_mstack *ft_mstack_findaddr(t_mstack *root, void *addr) {
    while (root != NULL && (uintptr_t)addr < (uintptr_t) root) {
        if ((uintptr_t)root - root->size + sizeof(*root) <= (uintptr_t)addr)
            return (root);
        root = root->next;
    }
    return (NULL);
}
