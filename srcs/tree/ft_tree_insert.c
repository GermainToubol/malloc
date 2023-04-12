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

/*
 * https://rosettacode.org/wiki/Red_black_trees
 * Based on the rosettacode C# RBTree implementation
 *
 * Distributed under Creative Commons Attribution-ShareAlike 4.0 International
 * (CC BY-SA 4.0)
 * https://creativecommons.org/licenses/by-sa/4.0/
 */

#include "ft_tree.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static void _right_rotate(t_node *node, t_node **root) {
    t_node *left;

    left       = node->left;
    node->left = left->right;
    if (left->right != NULL)
        left->right->parent = node;
    left->parent = node->parent;

    if (node->parent == NULL)
        *root = left;
    else if (node == node->parent->right)
        node->parent->right = left;
    else
        node->parent->left = left;
    left->right  = node;
    node->parent = left;
}

static void _left_rotate(t_node *node, t_node **root) {
    t_node *right;

    right       = node->right;
    node->right = right->left;
    if (right->left != NULL) {
        right->left->parent = node;
    }
    right->parent = node->parent;

    if (node->parent == NULL)
        *root = right;
    else if (node == node->parent->left)
        node->parent->left = right;
    else
        node->parent->right = right;
    right->left  = node;
    node->parent = right;
}

static bool is_black_node(t_node *node) {
    if (node == NULL || node->color == COLOR_BLACK)
        return (true);
    return (false);
}

typedef void (*t_rotate)(t_node *, t_node **);

static t_node *_ft_balence_insert(t_node *node, t_node **root) {
    t_node *       uncle;
    bool           is_on_left;
    const t_rotate tab[2] = { _left_rotate, _right_rotate };

    node->color           = COLOR_RED;
    while (node->parent != NULL && node->parent->color == COLOR_RED) {
        uncle      = (t_node *)((uintptr_t)node->parent->parent->left
                           + (uintptr_t)node->parent->parent->right
                           - (uintptr_t)node->parent);
        is_on_left = (node->parent == node->parent->parent->left);
        if (!is_black_node(uncle)) {
            node->parent->color         = COLOR_BLACK;
            uncle->color                = COLOR_BLACK;
            node->parent->parent->color = COLOR_RED;
            node                        = node->parent->parent;
        }
        else {
            if ((is_on_left && node == node->parent->right)
                || (!is_on_left && node == node->parent->left)) {
                node = node->parent;
                tab[is_on_left ? 0 : 1](node, root);
            }
            node->parent->color         = COLOR_BLACK;
            node->parent->parent->color = COLOR_RED;
            tab[is_on_left ? 1 : 0](node->parent->parent, root);
        }
    }
    (*root)->color = COLOR_BLACK;
    return (*root);
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
    _ft_balence_insert(new, &root);
    return (root);
}

/**
 * @fn t_node *ft_tree_delete(t_node *root, t_node *old)
 * @param root: root of the tree
 * @param old: node to remove
 * @return updated root
 */
t_node *ft_tree_delete(t_node *root, t_node *z) {
    t_node *y;
    t_node *x;
    t_node *x_parent;

    if (z == NULL)
        return (root);
    y        = z;
    x        = NULL;
    x_parent = NULL;
    if (y->left == NULL)
        x = y->right;
    else if (y->right == NULL)
        x = y->left;
    else {
        y = y->right;
        while (y->left != NULL)
            y = y->left;
        x = y->right;
    }
    if (y != z) {
        z->left->parent = y;
        y->left         = z->left;
        if (y != z->right) {
            x_parent = y->parent;
            if (x != NULL)
                x->parent = y->parent;
            y->parent->left  = x;
            y->right         = z->right;
            y->right->parent = y;
        }
        else
            x_parent = y;

        if (root == z || z->parent == NULL)
            root = y;
        else if (z->parent->left == z)
            z->parent->left = y;
        else
            z->parent->right = y;
        y->parent       = z->parent;
        uint64_t coltmp = y->color;
        y->color        = z->color;
        z->color        = coltmp;
        y               = z;
    }
    else {
        x_parent = y->parent;
        if (x != NULL)
            x->parent = y->parent;
        if (root == z || z->parent == NULL)
            root = x;
        else if (z->parent->left == z)
            z->parent->left = x;
        else
            z->parent->right = x;
    }
    if (y->color != COLOR_RED) {
        while (x != root && (x == NULL || x->color == COLOR_BLACK)) {
            if (x == x_parent->left) // Replace like upward
            {
                t_node *w = x_parent->right;
                if (w->color == COLOR_RED) {
                    w->color        = COLOR_BLACK;
                    x_parent->color = COLOR_RED;
                    _left_rotate(x_parent, &root);
                    w = x_parent->right;
                }
                if (is_black_node(w->left) && is_black_node(w->right)) {
                    w->color = COLOR_RED;
                    x        = x_parent;
                    x_parent = x_parent->parent;
                }
                else {
                    if (is_black_node(w->right)) {
                        if (w->left != NULL)
                            w->left->color = COLOR_BLACK;
                        w->color = COLOR_RED;
                        _right_rotate(w, &root);
                        w = x_parent->right;
                    }
                    w->color        = x_parent->color;
                    x_parent->color = COLOR_BLACK;
                    if (w->right != NULL)
                        w->right->color = COLOR_BLACK;
                    _left_rotate(x_parent, &root);
                    break;
                }
            }
            else {
                t_node *w = x_parent->left;
                if (w->color == COLOR_RED) {
                    w->color        = COLOR_BLACK;
                    x_parent->color = COLOR_RED;
                    _right_rotate(x_parent, &root);
                    w = x_parent->left;
                }
                if (is_black_node(w->left) && is_black_node(w->right)) {
                    w->color = COLOR_RED;
                    x        = x_parent;
                    x_parent = x_parent->parent;
                }
                else {
                    if (is_black_node(w->left)) {
                        if (w->right != NULL)
                            w->right->color = COLOR_BLACK;
                        w->color = COLOR_RED;
                        _left_rotate(w, &root);
                        w = x_parent->left;
                    }
                    w->color        = x_parent->color;
                    x_parent->color = COLOR_BLACK;
                    if (w->left != NULL)
                        w->left->color = COLOR_BLACK;
                    _right_rotate(x_parent, &root);
                    break;
                }
            }
        }
        if (x != NULL)
            x->color = COLOR_BLACK;
    }
    return (root);
}
