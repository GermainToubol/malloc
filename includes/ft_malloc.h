/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:13:34 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/11 16:13:34 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_malloc.h
 */
#ifndef FT_MALLOC_H
#define FT_MALLOC_H

#include "ft_heap.h"
#include "ft_mstack.h"
#include "ft_small.h"
#include "ft_tiny.h"
#include "ft_tree.h"

#define TINY_THRESHOLD  TINY_DATA_SIZE
#define LARGE_THRESHOLD SMALL_DATA_SIZE

/**
 * @struct t_root
 * @brief contains the information about the roots
 */
typedef struct s_root {
    t_mstack *mroot;  /*!< Root of memory stack */
    t_node *  sroot;  /*!< Root of tree */
    t_queue   qtiny;  /*!< Tiny blocks priority queue */
    t_queue   qsmall; /*!< Small blocks priority queue */
} t_root;

extern t_root g_master;

#define REAL_SIZE(x) (x->size & ~BLOCK_MASK)

void *malloc(size_t size);
void  free(void *addr);
void *realloc(void *addr, size_t size);

#endif /* FT_MALLOC_H */
