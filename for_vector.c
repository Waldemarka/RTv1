/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 12:15:47 by vomelchu          #+#    #+#             */
/*   Updated: 2018/09/30 12:15:49 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	vect_sub(t_vector *vec_1, t_vector *vec_2)
{
	t_vector result;

	result.x = vec_1->x - vec_2->x;
	result.y = vec_1->y - vec_2->y;
	result.z = vec_1->z - vec_2->z;
	return (result);
}

t_vector	vect_add(t_vector *vec_1, t_vector *vec_2)
{
	t_vector result;

	result.x = vec_1->x + vec_2->x;
	result.y = vec_1->y + vec_2->y;
	result.z = vec_1->z + vec_2->z;
	return (result);
}

t_vector	scale(t_vector *vec_1, double c)
{
	t_vector result;

	result.x = vec_1->x * c;
	result.y = vec_1->y * c;
	result.z = vec_1->z * c;
	return (result);
}

double		vect_dot(t_vector *vec_1, t_vector *vec_2)
{
	return (vec_1->x * vec_2->x + vec_1->y * vec_2->y + vec_1->z * vec_2->z);
}

t_vector	vect_norm(t_vector *vec_1)
{
	double		len;
	t_vector	vec;

	len = sqrt(vect_dot(vec_1, vec_1));
	vec.x = vec_1->x / len;
	vec.y = vec_1->y / len;
	vec.z = vec_1->z / len;
	return (vec);
}
