/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:49:39 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/11 22:49:39 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_tree_insert.c
 */

#include "ft_tree.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static void _right_rotate(t_node *node) {
    t_node *left;

    left       = node->left;
    node->left = left->right;
    if (left->right != NULL)
        left->right->parent = node;
    left->parent = node->parent;

    if (node->parent == NULL)
        ;
    else if (node == node->parent->right)
        node->parent->right = left;
    else
        node->parent->left = left;
    left->right  = node;
    node->parent = left;
}

static void _left_rotate(t_node *node) {
    t_node *right;

    right       = node->right;
    node->right = right->left;
    if (right->left != NULL) {
        right->left->parent = node;
    }
    right->parent = node->parent;

    if (node->parent == NULL)
        ;
    else if (node == node->parent->left)
        node->parent->left = right;
    else
        node->parent->right = right;
    right->left  = node;
    node->parent = right;
}

static bool is_back_node(t_node *node) {
    if (node == NULL || node->color == COLOR_BLACK)
        return (true);
    return (false);
}

typedef void (*t_rotate)(t_node *);

t_node *_ft_balence_insert(t_node *node) {
    t_node *       uncle;
    bool           is_on_left;
    const t_rotate tab[2] = { _left_rotate, _right_rotate };

    node->color           = COLOR_RED;
    while (node->parent != NULL && node->parent->color == COLOR_RED) {
        uncle      = (t_node *)((uintptr_t)node->parent->parent->left
                           + (uintptr_t)node->parent->parent->right
                           - (uintptr_t)node->parent);
        is_on_left = (node->parent == node->parent->parent->left);
        if (!is_back_node(uncle)) {
            node->parent->color         = COLOR_BLACK;
            uncle->color                = COLOR_BLACK;
            node->parent->parent->color = COLOR_RED;
            node                        = node->parent->parent;
        }
        else {
            if ((is_on_left && node == node->parent->right)
                || (!is_on_left && node == node->parent->left)) {
                node = node->parent;
                tab[is_on_left ? 0 : 1](node);
            }
            node->parent->color         = COLOR_BLACK;
            node->parent->parent->color = COLOR_RED;
            tab[is_on_left ? 1 : 0](node->parent->parent);
        }
    }
    return (node);
}

/**
 * @fn t_node *ft_tree_insert(t_node *root, t_node *new)
 * @param root: root of the tree
 * @param new: new node
 * @return updated root
 */
t_node *ft_tree_insert(t_node *root, t_node *new) {
    t_node *tmp;
    t_node *prev;

    if (root == NULL)
        return (new);
    tmp = root;
    while (tmp != NULL) {
        prev = tmp;
        if (new->size < tmp->size)
            tmp = tmp->left;
        else
            tmp = tmp->right;
    }
    if (prev->size > new->size)
        prev->left = new;
    else
        prev->right = new;
    new->parent = prev;
    _ft_balence_insert(new);
    root = new;
    while (root->parent != NULL)
        root = root->parent;
    root->color = COLOR_BLACK;
    return (root);
}
