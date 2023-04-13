/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gdata_set_area.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:51:41 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/11 17:51:41 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_gdata_set_area.c
 */

#include "ft_gdata.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @fn void ft_gdata_set_area(void *area, size_t size, bool prev, bool next)
 * @param area: new memory zone
 * @param size: size of the memory zone
 * @param mergeprev: preceeding area is already used
 * @param mergenext: following area is already used
 */
void ft_gdata_set_area(void *area, size_t size, bool prev, bool next) {
    t_gdata *data;
    t_gdata *last;

    data = (t_gdata *)area;
    last = (t_gdata *)((uint8_t *)area + size - sizeof(*data));
    if (area == NULL || size < 2 * sizeof(t_gdata))
        return;
    data->prevsize = 0;
    if (prev) {
        data--;
        size += sizeof(*data);
        size |= data->size & BLOCK_USED;
    }
    last->size = 0;
    if (next) {
        last++;
        size += sizeof(*data);
    }
    data->size     = size - sizeof(*data);
    last->prevsize = data->size & ~BLOCK_USED;
    ft_gdata_free(data);
}
