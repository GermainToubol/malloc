/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mstack_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:39:41 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/06 17:39:41 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_mstack_init.c
 */

#include "ft_mstack.h"

#include <stddef.h>

/**
 * @fn void ft_mstack_init(t_mstack *current)
 * @param current: the new stack-chunk
 */
void ft_mstack_init(t_mstack *current, size_t size) {
    current->previous = NULL;
    current->next     = NULL;
    current->size     = size;
}
