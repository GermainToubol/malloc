/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:55:25 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/11 22:55:25 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_tree.h
 */

#ifndef FT_TREE_H
#define FT_TREE_H

#include <stdint.h>

/**
 * @struct t_node
 * @brief node of the tree
 */
typedef struct s_node {
    struct s_node *parent;
    struct s_node *left;
    struct s_node *right;
    uint64_t       color;
    uint64_t       size;
} t_node;

#define COLOR_BLACK 0
#define COLOR_RED   1

void           ft_node_init(t_node *node, uint64_t size);
t_node *       ft_tree_insert(t_node *root, t_node *new);
t_node *       ft_tree_delete(t_node *root, t_node *old);
t_node *       ft_tree_search(t_node *root, uint64_t size);

extern t_node *g_root; /* Temporary, needs to be removed */

#endif /* FT_TREE_H */
