/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_small.h                                          :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:16:37 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/18 20:16:37 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_small.h
 * @brief SMALL allocation spaces
 */

#ifndef FT_SMALL_H
#define FT_SMALL_H

#include "ft_heap.h"

#include <stdint.h>

/**
 * @define SMALL_DATA_SIZE
 * @brief number of bytes allocated on a single small allocation
 */
#define SMALL_DATA_SIZE  255

/**
 * @define SMALL_TABLE_SIZE
 * @brief size of the allocation table for small chunks
 */
#define SMALL_TABLE_SIZE 2

#define N_SMALLS         128

#define SMALL_MASK_A     ((uint64_t)-1)
#define SMALL_MASK_B     ((uint64_t)-1)

/**
 * @typedef t_small_data
 * @brief Allocated chunk on a single small allocation request
 */
typedef uint8_t t_small_data[SMALL_DATA_SIZE];

/**
 * @struct t_small
 * @brief contain the small allocation blocks
 */
typedef struct s_small {
    t_heap       node;
    uint64_t     table[SMALL_TABLE_SIZE];
    t_small_data data[];
} t_small;

void  ft_small_init(t_small *small);
void *ft_small_alloc(t_small *block);
void  ft_small_free(t_small *block, void *addr);
void  ft_small_delete(t_small *chunk);

#endif /* FT_SMALL_H */
