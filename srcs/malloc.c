/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:28:13 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/13 20:28:13 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file malloc.c
 */

#include "ft_malloc.h"

#include <stddef.h>

t_root g_master = { .mroot = NULL, .sroot = NULL };

void * malloc(size_t size) {
    (void)size;
    return (NULL);
}
