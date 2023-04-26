/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 08:38:23 by gtoubol           #+#    #+#             */
/*   Updated: 2023/04/26 08:38:23 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file malloc.h
 */

#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>

void *malloc(size_t size);
void  free(void *addr);
void *realloc(void *addr, size_t size);
void  show_alloc_mem(void);
void  show_alloc_mem_ex(void);

#endif /* MALLOC_H */
