/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 11:59:26 by vomelchu          #+#    #+#             */
/*   Updated: 2018/09/30 11:59:29 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		cos_sphe(t_data  *data, t_ray *ray, int q)
{
	double a;
	double b;
	double c;
	int i;

	i = -1;
	while (++i != data->sph)
	{
		data->dist = vect_sub(&ray->start, &data->spheres[i].pos);
		a = vect_dot(&ray->dir, &ray->dir);
		b = 2 * vect_dot(&ray->dir, &data->dist);
		c = vect_dot(&data->dist, &data->dist) - (data->spheres[i].radius
			* data->spheres[i].radius);
		data->discr = b * b - 4 * a * c;
		if (data->discr < 0)
			continue;
		else
		{
			data->sqrt_discr = sqrtl(data->discr);
			data->t_0 = (-b + data->sqrt_discr) / (2 * a);
			data->t_1 = (-b - data->sqrt_discr) / (2 * a);
			if (data->t_0 > data->t_1)
				data->t_0 = data->t_1;
			if((data->t_0 > 0.001) && (data->t_0 < data->t))
			{
				data->t = data->t_0;
				data->is_it_spher = i;
				if (q == 1)
					data->material = data->materials[data->spheres[i].material];
				data->nb_figur = 0;
			}
		}
	}
}

void		cos_plane(t_data  *data, t_ray *ray, int j)
{
	double a;
	double b;
	t_vector q;
	int i;

	i = -1;
	while (++i != data->pln)
	{
		data->plane[i].dir = vect_norm(&data->plane[i].dir);
		data->dist = vect_sub(&ray->start, &data->plane[i].pos);
		if (vect_dot(&data->dist, &data->plane[i].dir) < 0)
			data->plane[i].dir = scale(&data->plane[i].dir, -1);
		q = scale(&data->dist, -1);
		a = vect_dot(&q, &data->plane[i].dir);
		b = vect_dot(&ray->dir, &data->plane[i].dir);
		if (b != 0)
		{
			data->t = a / b;
			data->is_it_spher = i;
			if (j == 1)
				data->material = data->materials[data->plane[i].material];
			data->nb_figur = 3;
		}
		else
			data->t = 20000;
	
	}
}

void		cos_cyl(t_data *data, t_ray *ray, int q)
{
	double a;
	double b;
	double c;
	int i;

	i = -1;
	while (++i != data->clndr)
	{
		data->cylinder[i].dir = vect_norm(&data->cylinder[i].dir);
		data->dist = vect_sub(&ray->start, &data->cylinder[i].pos);
		a = vect_dot(&ray->dir, &ray->dir) - pow(vect_dot(&ray->dir, &data->cylinder[i].dir), 2);
		b = 2 * (vect_dot(&ray->dir, &data->dist) - vect_dot(&ray->dir, &data->cylinder[i].dir) *
			vect_dot(&data->dist, &data->cylinder[i].dir));
		c = vect_dot(&data->dist, &data->dist) - pow(vect_dot(&data->dist, &data->cylinder[i].dir), 2) -
		pow(data->cylinder[i].radius, 2);
		data->discr = b * b - 4 * a * c;
		if (data->discr < 0)
			continue;
		else
		{
			data->sqrt_discr = sqrtl(data->discr);
			data->t_0 = (-b + data->sqrt_discr) / (2 * a);
			data->t_1 = (-b - data->sqrt_discr) / (2 * a);
			if (data->t_0 > data->t_1)
				data->t_0 = data->t_1;
			if((data->t_0 > 0.001) && (data->t_0 < data->t))
			{
				data->t = data->t_0;
				data->is_it_spher = i;
				if (q == 1)
				data->material = data->materials[data->cylinder[i].material];
				data->nb_figur = 1;
			}
		}
	}
}

void		cos_cone(t_data *data, t_ray *ray, int q)
{
	double a;
	double b;
	double c;
	int i;

	i = -1;
	while (++i != data->cn)
	{
		data->cone[i].dir = vect_norm(&data->cone[i].dir);
		data->dist = vect_sub(&ray->start, &data->cone[i].pos);
		a = vect_dot(&ray->dir, &ray->dir) - (1 + (data->cone[i].k * data->cone[i].k)) *
		pow(vect_dot(&ray->dir, &data->cone[i].dir), 2);
		b = (vect_dot(&ray->dir, &data->dist) - (1 + (data->cone[i].k  * data->cone[i].k)) *
			vect_dot(&ray->dir, &data->cone[i].dir) * vect_dot(&data->dist, &data->cone[i].dir));
		c = vect_dot(&data->dist, &data->dist) - (1 + (data->cone[i].k * data->cone[i].k)) *
			pow(vect_dot(&data->dist, &data->cone[i].dir), 2);
		data->discr = b * b - a * c;
		if (data->discr < 0)
			continue;
		else
		{
			data->sqrt_discr = sqrtl(data->discr);
			data->t_0 = (-b + data->sqrt_discr) / (a);
			data->t_1 = (-b - data->sqrt_discr) / (a);
			if (data->t_0 > data->t_1)
				data->t_0 = data->t_1;
			if((data->t_0 > 0.001) && (data->t_0 < data->t))
			{
				data->t = data->t_0;
				data->is_it_spher = i;
				if (q == 1)
					data->material = data->materials[data->cone[i].material];
				data->nb_figur = 2;
			}
		}
	}
}
