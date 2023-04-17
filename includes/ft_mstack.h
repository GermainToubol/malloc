/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mstack.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:22:09 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/06 17:22:09 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_mstack.h
 * @brief stack like succession of mmaped areas
 */

#ifndef FT_MSTACK_H
#define FT_MSTACK_H

#include <stddef.h>

/**
 * @struct t_mstack
 * @brief mmap stack header
 *
 * Header will be at root of the stack
 */
typedef struct s_mstack {
    struct s_mstack *previous; /*!< Previous stack-like address */
    struct s_mstack *next;     /*!< Next stack-like address */
    size_t           size;     /*!< Size of the stack */
} t_mstack;

/* Functions *****************************************************************/
void      ft_mstack_init(t_mstack *current, size_t size);
t_mstack *ft_mstack_extend(t_mstack *root, size_t size);
t_mstack *ft_mstack_findaddr(t_mstack *root, void *addr);

#endif /* FT_MSTACK_H */
