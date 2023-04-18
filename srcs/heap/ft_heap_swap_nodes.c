/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heap_swap_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:00:31 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/18 19:00:31 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_heap_swap_nodes.c
 * @brief swap two nodes in the heap
 */

#include "ft_heap.h"

static void _update_node(t_queue *queue, t_heap *node, t_heap *ref) {
    if (node->prev == node)
        node->prev = ref;
    if (node->parent == node)
        node->parent = ref;
    if (node->left == node)
        node->left = ref;
    if (node->right == node)
        node->right = ref;
    if (node->next == node)
        node->next = ref;

    if (node->prev)
        node->prev->next = node;
    else
        queue->head = node;
    if (node->next)
        node->next->prev = node;
    else
        queue->tail = node;
    if (node->parent) {
        if (node->parent->left == ref)
            node->parent->left = node;
        else if (node->parent->right == ref)
            node->parent->right = node;
    }
    if (node->left)
        node->left->parent = node;
    if (node->right)
        node->right->parent = node;
}

/**
 * @fn void ft_heap_swap_nodes(t_queue *queue, t_heap *a, t_heap *b)
 * @param queue: current priority queue
 * @param a: first node to swap
 * @param b: second node to swap
 */
void ft_heap_swap_nodes(t_queue *queue, t_heap *a, t_heap *b) {
    // Swap content
    t_heap tmp;

    tmp = *a;
    *a  = *b;
    *b  = tmp;

    // Restore prev/next
    _update_node(queue, a, b);
    _update_node(queue, b, a);
}
