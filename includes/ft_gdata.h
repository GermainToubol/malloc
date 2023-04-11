/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gdata.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:03:09 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/07 16:03:09 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
 * @file ft_gdata.h
 * @brief wrapper around the datas
 */

#ifndef FT_GDATA_H
#define FT_GDATA_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @struct t_gdata
 * @brief wrapper around the datas containers
 */
typedef struct s_gdata {
    uint64_t prevsize; /*!< Size of previous block */
    uint64_t size;     /*!< Size of the current block */
    uint8_t  data[];   /*!< Data or information about free blocks */
} t_gdata;

/**
 * @struct t_free
 * @brief indication on previous/next freeblock
 */
typedef struct s_free {
    t_gdata *previous;
    t_gdata *next;
} t_free;

#define BLOCK_FREE  0b000UL
#define BLOCK_USED  0b001UL
#define BLOCK_TINY  0b010UL
#define BLOCK_SMALL 0b100UL
#define BLOCK_OTHER 0b110UL
#define BLOCK_MASK  0b111UL

bool  ft_gdata_init(t_gdata *data, size_t size);
void  ft_gdata_free(t_gdata *data);
void  ft_gdata_set_area(void *area, size_t size, bool prev, bool next);
void *ft_gdata_alloc(t_gdata *data, size_t size, uint8_t type);

#endif /* FT_GDATA_H */
