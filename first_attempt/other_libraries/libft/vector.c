/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:45:37 by akovalev          #+#    #+#             */
/*   Updated: 2024/07/19 15:52:48 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*A function vec_new which will take a pointer to 
a t_vec and allocate len * elem_size bytes in 
the buffer as well as initialize its length and element size.*/
int	vec_new(t_vec *dst, size_t init_len, size_t elem_size)
{
	if (!dst || elem_size == 0)
		return (-1);
	dst->len = 0;
	dst->elem_size = elem_size;
	dst->alloc_size = init_len * elem_size;
	if (init_len == 0)
		dst->memory = NULL;
	else
	{
		dst->memory = malloc(dst->alloc_size);
		if (!dst->memory)
			return (-1);
	}
	return (1);
}

/*A function vec_free that frees the allocated 
resources in src and zeroes its fields.*/
void	vec_free(t_vec *src)
{
	if (!src)
		return ;
	free(src->memory);
	src->memory = NULL;
	src->alloc_size = 0;
	src->elem_size = 0;
	src->len = 0;
}

/*A function vec_resize which will take in a 
target_size parameter and either shrink (destructively)
 or grow the vector to the target size, 
 copying the old contents over to the new allocation.*/
int	vec_resize(t_vec *src, size_t target_len)
{
	unsigned char	*temp;

	if (!src)
		return (-1);
	else if (!src->memory)
		return (vec_new(src, target_len, src->elem_size));
	src->alloc_size = target_len * src->elem_size;
	temp = src->memory;
	src->memory = malloc(src->alloc_size);
	if (!src->memory)
		return (-1);
	if (ft_memmove(src->memory, temp, src->len * src->elem_size) == NULL)
		return (-1);
	free(temp);
	temp = NULL;
	return (1);
}

/* A function vec_get which returns an opaque handle to the element at index*/
void	*vec_get(t_vec *src, size_t index)
{
	if (!src || index >= src->len || !src->memory)
		return (NULL);
	return (&(src->memory[src->elem_size * index]));
}

/*A function vec_push which takes in a vector and a 
pointer to an element to be pushed to the end of the vector.*/
int	vec_push(t_vec *dst, void *src)
{
	if (!dst || !src)
		return (-1);
	else if (!dst->memory)
		if (vec_new(dst, 1, dst->elem_size) == -1)
			return (-1);
	if (dst->elem_size * dst->len >= dst->alloc_size)
		if (vec_resize(dst, dst->len * 2) < 0)
			return (-1);
	ft_memmove(&dst->memory[dst->len * dst->elem_size], src, dst->elem_size);
	dst->len++;
	return (1);
}