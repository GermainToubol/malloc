/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:31:00 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/12 19:31:00 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_tree_search.c
 */

#include "ft_tree.h"

#include <stddef.h>
#include <stdint.h>

/**
 * @fn t_node *ft_tree_search(t_node *root, uint64_t size)
 * @param root: root of the tree
 * @param size: requested minimal size
 * @return pointer to the node of the node with the minimal size containing
 * size, NULL if none are found.
 */
t_node *ft_tree_search(t_node *root, uint64_t size) {
    t_node *bigger = NULL;

    if (root == NULL)
        return (NULL);
    while (root != NULL) {
        if (root->size == size)
            return (root);
        if (root->size > size) {
            bigger = root;
            root   = root->left;
            continue;
        }
        root = root->right;
    }
    return (bigger);
}
