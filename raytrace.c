/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 12:25:29 by vomelchu          #+#    #+#             */
/*   Updated: 2018/09/30 12:25:51 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
# define EXIT (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)


void		ini_date(t_data *data)
{
	data->red = 0;
	data->green = 0;
	data->blue = 0;
	data->coef = 1;
	data->ray.start.x = data->x + data->camera.pos.x;
	data->ray.start.y = data->y + data->camera.pos.y;
	data->ray.start.z = -2000 + + data->camera.pos.z;
	data->ray.dir.x = 0 + data->camera.dir.x;
	data->ray.dir.y = 0 + data->camera.dir.y;
	data->ray.dir.z = 1 + data->camera.dir.z;
	data->level = 0;
}

void	val_light(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->lght)
	{
		data->dist = vect_sub(&data->lights[i].pos, &data->new_start);
		if (vect_dot(&data->n, &data->dist) <= 0)
			continue;
		data->t = sqrtl(vect_dot(&data->dist, &data->dist));
		if (data->t <= 0)
			continue;
		data->ray_of_light.start = data->new_start;
		data->ray_of_light.dir = scale(&data->dist, (1 / data->t));
		data->is_it_spher = -1;
		cos_sphe(data, &data->ray_of_light, 2);
		cos_cyl(data, &data->ray_of_light, 2);
		cos_cone(data, &data->ray_of_light, 2);
		//cos_plane(data, &data->ray_of_light, 2);
		if (data->is_it_spher == -1)
		{
			data->lamb = vect_dot(&data->ray_of_light.dir, &data->n) * data->coef;
			data->red += data->lamb * data->lights[i].intensity.red * data->material.diffuse.red;
			data->green += data->lamb * data->lights[i].intensity.green * data->material.diffuse.green;
			data->blue += data->lamb * data->lights[i].intensity.blue * data->material.diffuse.blue;
		}
	}	
	data->coef *= data->material.reflection;
}

t_vector	choose_nb_fig(t_data *data)
{
	t_vector *vec;

	vec = NULL;
	if (data->nb_figur == 0)
		return (vect_sub(&data->new_start, &data->spheres[data->is_it_spher].pos));
	else if (data->nb_figur == 1)
		return (vect_sub(&data->new_start, &data->cylinder[data->is_it_spher].pos));
	else if (data->nb_figur == 2)
		return (vect_sub(&data->new_start, &data->cone[data->is_it_spher].pos));
	else if (data->nb_figur == 3)
		return (vect_sub(&data->new_start, &data->plane[data->is_it_spher].pos));
	return (*vec);
}

int		cont_draw(t_data *data)
{
	if(data->is_it_spher == -1)
		return (0);
	data->scaled = scale(&data->ray.dir, data->t);
	data->new_start = vect_add(&data->ray.start, &data->scaled);
	data->n = choose_nb_fig(data);
	data->tmp = vect_dot(&data->n, &data->n);
	if (data->tmp == 0)
		return (0);
	data->tmp = 1.0 / sqrtl(data->tmp);
	data->n = scale(&data->n, data->tmp);
	return (1);
}

void	draw(t_data *data)
{
	data->y = -1;
	while (++data->y < HEIGHT)
	{
		data->x = -1;
		while (++data->x < WIDTH)
		{
			ini_date(data);
			while (data->coef > 0.0 && data->level < 15)
			{
				data->is_it_spher = -1;
				data->t = 20000.0;
				cos_sphe(data, &data->ray, 1);
				cos_cyl(data, &data->ray, 1);
				cos_cone(data, &data->ray, 1);
				//cos_plane(data, &data->ray, 1);
				if (!cont_draw(data))
					break;
				val_light(data);
				data->ray.start = data->new_start;
				data->temp = scale(&data->n, 2 * vect_dot(&data->ray.dir, &data->n));
				data->ray.dir = vect_sub(&data->ray.dir, &data->temp);
				data->level++;
			}
			put_color(data);
		}
	}
}
