/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 06:45:55 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/13 06:45:55 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_node_init.c
 */

#include "ft_tree.h"

#include <stddef.h>
#include <stdint.h>

/**
 * @fn void ft_node_init(t_node *node, uint64_t size)
 * @param node: current node
 * @param size: node size
 */
void ft_node_init(t_node *node, uint64_t size) {
    if (node == NULL)
        return;
    node->parent = NULL;
    node->left   = NULL;
    node->right  = NULL;
    node->size   = size;
    node->color  = 1;
}
