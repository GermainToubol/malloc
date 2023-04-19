/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tiny.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:16:37 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/18 20:16:37 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_tiny.h
 * @brief TINY allocation spaces
 */

#ifndef FT_TINY_H
#define FT_TINY_H

#include "ft_heap.h"

#include <stdint.h>

/**
 * @define TINY_DATA_SIZE
 * @brief number of bytes allocated on a single tiny allocation
 */
#define TINY_DATA_SIZE  40

/**
 * @define TINY_TABLE_SIZE
 * @brief size of the allocation table for tiny chunks
 */
#define TINY_TABLE_SIZE 2

#define N_TINYS         101

#define TINY_MASK_A     ((uint64_t)-1)
#define TINY_MASK_B     (~((uint64_t)-1 << (N_TINYS - 64)))

/**
 * @typedef t_tiny_data
 * @brief Allocated chunk on a single tiny allocation request
 */
typedef uint8_t t_tiny_data[TINY_DATA_SIZE];

/**
 * @struct t_tiny
 * @brief contain the tiny allocation blocks
 */
typedef struct s_tiny {
    t_heap      node;
    uint64_t    table[TINY_TABLE_SIZE];
    t_tiny_data data[];
} t_tiny;

void  ft_tiny_init(t_tiny *tiny);
void *ft_tiny_alloc(t_tiny *block);
void  ft_tiny_free(t_tiny *block, void *addr);
void  ft_tiny_delete(t_tiny *chunk);

#endif /* FT_TINY_H */
