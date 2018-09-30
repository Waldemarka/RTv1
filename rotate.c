/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 13:06:41 by vomelchu          #+#    #+#             */
/*   Updated: 2018/09/30 13:31:10 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	rotate_x(t_vector o, double a)
{
	t_vector d;

	d.x = o.x;
	d.y = o.y * cos(a) + o.z * sin(a);
	d.z = o.z * cos(a) - o.y * sin(a);
	return (d);
}

t_vector	rotate_y(t_vector o, double a)
{
	t_vector d;

	d.x = o.x * cos(a) + o.z * sin(a);
	d.y = o.y;
	d.z = o.z * cos(a) - o.x * sin(a);
	return (d);
}

t_vector	rotate_z(t_vector o, double a)
{
	t_vector d;

	d.x = o.x * cos(a) - o.y * sin(a);
	d.y = o.x * sin(a) + o.y * cos(a);
	d.z = o.z;
	return (d);
}

t_vector	rotate(t_vector o, double a, double b, double g)
{
	t_vector d;

	d = o;
	d = rotate_x(d, a);
	d = rotate_y(d, b);
	d = rotate_z(d, g);
	return (d);
}
