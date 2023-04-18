/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:05:12 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/18 12:05:12 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_queue_push.c
 */

#include "ft_heap.h"

#include <stddef.h>
#include <stdint.h>

static inline void _node_init(t_heap *node) {
    *node = (t_heap) { NULL, NULL, NULL, NULL, NULL };
}

static void _insert_node(t_queue *queue, t_heap *node) {
    if (queue->tail != NULL) {
        t_heap *parent;

        queue->tail->next = node;
        node->prev        = queue->tail;

        if (queue->tail->parent == NULL)
            parent = queue->tail;
        else
            parent = queue->tail->parent;
        if (parent->left == NULL)
            parent->left = node;
        else if (parent->right == NULL)
            parent->right = node;
        else {
            parent       = parent->next;
            parent->left = node;
        }
        node->parent = parent;
    }
    if (queue->head == NULL)
        queue->head = node;
    queue->tail = node;
}

static void _heap_sort_up(t_queue *queue, t_heap *node) {
    while (node->parent != NULL && (uintptr_t)node->parent < (uintptr_t)node) {
        ft_heap_swap_nodes(queue, node, node->parent);
    }
}

/**
 * @fn void ft_queue_push(t_queue *queue, t_heap *node)
 * @param queue: current priority queue
 * @param node: new element in the queue
 */
void ft_queue_push(t_queue *queue, t_heap *node) {
    if (queue == NULL || node == NULL)
        return;
    _node_init(node);
    _insert_node(queue, node);
    _heap_sort_up(queue, node);
}
