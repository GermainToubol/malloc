/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:45:34 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/18 11:45:34 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_heap.h
 * @brief implement a priority queue using a max heap
 */

#ifndef FT_HEAP_H
#define FT_HEAP_H

#include <stdint.h>

/**
 * @struct t_heap
 * @brief node of the priority queue
 */
typedef struct s_heap {
    struct s_heap *parent; /*!< parent node */
    struct s_heap *left;   /*!< left son */
    struct s_heap *right;  /*!< right son */
    struct s_heap *prev;   /*!< previous node */
    struct s_heap *next;   /*!< next node  */
} t_heap;

/**
 * @struct t_queue
 * @brief actual queue
 */
typedef struct s_queue {
    struct s_heap *head; /*!< Top node of the heap */
    struct s_heap *tail; /*!< Last node of the heap */
} t_queue;

/* Functions *****************************************************************/
void ft_queue_push(t_queue *queue, t_heap *node);
void ft_heap_swap_nodes(t_queue *queue, t_heap *a, t_heap *b);
void ft_queue_pop(t_queue *queue);
void ft_queue_remove_node(t_queue *queue, t_heap *node);

#endif /* FT_HEAP_H */
