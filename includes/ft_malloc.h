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
#include "ft_tree.h"

#define LARGE_THRESHOLD 256

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

#endif /* FT_MALLOC_H */
