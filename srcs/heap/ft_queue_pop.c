/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:02:46 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/18 19:02:46 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_queue_pop.c
 */

#include "ft_heap.h"

#include <stddef.h>
#include <stdint.h>

static void _remove_tail(t_queue *queue) {
    t_heap *node;

    node = queue->tail;
    if (node->parent->left == node)
        node->parent->left = NULL;
    else
        node->parent->right = NULL;
    node->prev->next = NULL;
    queue->tail      = node->prev;
}

static void _heap_balance_down(t_queue *queue, t_heap *node) {
    while ((uintptr_t)node < (uintptr_t)node->left
           || (uintptr_t)node < (uintptr_t)node->right) {
        if ((uintptr_t)node->right < (uintptr_t)node->left)
            ft_heap_swap_nodes(queue, node, node->left);
        else
            ft_heap_swap_nodes(queue, node, node->right);
    }
}

/**
 * @fn void ft_queue_pop(t_queue *queue)
 * @param queue: current priority queue
 */
void ft_queue_pop(t_queue *queue) {
    if (queue == NULL)
        return;

    // Pop single element
    if (queue->head == queue->tail) {
        queue->head = NULL;
        queue->tail = NULL;
        return;
    }

    ft_heap_swap_nodes(queue, queue->head, queue->tail);
    _remove_tail(queue);
    _heap_balance_down(queue, queue->head);
}

/**
 * @fn void ft_queue_remove_node(t_queue *queue, t_heap *node)
 * @param queue: current queue
 * @param node: node to remove
 */
void ft_queue_remove_node(t_queue *queue, t_heap *node) {
    if (node == NULL || queue == NULL)
        return;

    if (node == queue->head) {
        ft_queue_pop(queue);
        return;
    }

    if (node == queue->tail) {
        _remove_tail(queue);
        return;
    }

    t_heap *tmp;
    tmp = queue->tail;
    ft_heap_swap_nodes(queue, node, queue->tail);
    _remove_tail(queue);
    _heap_balance_down(queue, tmp);
}
