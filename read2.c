/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 11:59:45 by vomelchu          #+#    #+#             */
/*   Updated: 2018/09/30 11:59:46 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	add_par_spheres(t_data *data, char **str, int q)
{
	data->spheres[data->sph].pos.x = ft_atoi(str[q + 1]);
	data->spheres[data->sph].pos.y = ft_atoi(str[q + 2]);
	data->spheres[data->sph].pos.z = ft_atoi(str[q + 3]);
	data->spheres[data->sph].radius = ft_atoi(str[q + 4]);
	if (ft_atoi(str[q + 5]) < data->nb_mtrl && ft_atoi(str[q + 5]) >= 0)
		data->spheres[data->sph].material = ft_atoi(str[q + 5]);
	else
		ft_error("BAD MATERIAL FOR SPHERES\n");
	data->sph++;
}

void	add_par_cylinder(t_data *data, char **str, int q)
{
	data->cylinder[data->clndr].pos.x = ft_atoi(str[q + 1]);
	data->cylinder[data->clndr].pos.y = ft_atoi(str[q + 2]);
	data->cylinder[data->clndr].pos.z = ft_atoi(str[q + 3]);
	data->cylinder[data->clndr].dir.x = ft_atoi(str[q + 4]);
	data->cylinder[data->clndr].dir.y = ft_atoi(str[q + 5]);
	data->cylinder[data->clndr].dir.z = ft_atoi(str[q + 6]);
	data->cylinder[data->clndr].radius = ft_atoi(str[q + 7]);
	if (ft_atoi(str[q + 8]) < data->nb_mtrl && ft_atoi(str[q + 8]) >= 0)
		data->cylinder[data->clndr].material = ft_atoi(str[q + 8]);
	else
		ft_error("BAD MATERIAL FOR CYLINDER\n");
	data->clndr++;
}

void	add_par_cone(t_data *data, char **str, int q)
{
	data->cone[data->cn].pos.x = ft_atoi(str[q + 1]);
	data->cone[data->cn].pos.y = ft_atoi(str[q + 2]);
	data->cone[data->cn].pos.z = ft_atoi(str[q + 3]);
	data->cone[data->cn].dir.x = ft_atoi(str[q + 4]);
	data->cone[data->cn].dir.y = ft_atoi(str[q + 5]);
	data->cone[data->cn].dir.z = ft_atoi(str[q + 6]);
	data->cone[data->cn].k = make_double(str[q + 7]);
	if (ft_atoi(str[q + 8]) < data->nb_mtrl && ft_atoi(str[q + 8]) >= 0)
		data->cone[data->cn].material = ft_atoi(str[q + 8]);
	else
		ft_error("BAD MATERIAL FOR CYLINDER\n");
	data->cn++;
}

void	add_par_plan(t_data *data, char **str, int q)
{
	data->plane[data->pln].pos.x = ft_atoi(str[q + 1]);
	data->plane[data->pln].pos.y = ft_atoi(str[q + 2]);
	data->plane[data->pln].pos.z = ft_atoi(str[q + 3]);
	data->plane[data->pln].dir.x = ft_atoi(str[q + 4]);
	data->plane[data->pln].dir.y = ft_atoi(str[q + 5]);
	data->plane[data->pln].dir.z = ft_atoi(str[q + 6]);
	if (ft_atoi(str[q + 7]) < data->nb_mtrl && ft_atoi(str[q + 7]) >= 0)
		data->plane[data->pln].material = ft_atoi(str[q + 7]);
	else
		ft_error("BAD MATERIAL FOR CYLINDER\n");
	data->pln++;
}

void	add_par_mat_lg(t_data *data, char **str, int q, int check)
{
	if (check == 1)
	{
		data->materials[data->mtrl].diffuse.red = ft_atoi(str[q + 1]);
		data->materials[data->mtrl].diffuse.green = ft_atoi(str[q + 2]);
		data->materials[data->mtrl].diffuse.blue = ft_atoi(str[q + 3]);
		data->materials[data->mtrl].reflection = make_double(str[q + 4]);
		data->mtrl++;
	}
	if (check == 2)
	{
		data->lights[data->lght].pos.x = ft_atoi(str[q + 1]);
		data->lights[data->lght].pos.y = ft_atoi(str[q + 2]);
		data->lights[data->lght].pos.z = ft_atoi(str[q + 3]);
		data->lights[data->lght].intensity.red = make_double(str[q + 4]);
		data->lights[data->lght].intensity.green = make_double(str[q + 5]);
		data->lights[data->lght].intensity.blue = ft_atoi(str[q + 6]);
		data->lght++;
	}
}
