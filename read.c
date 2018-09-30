/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 11:15:34 by vomelchu          #+#    #+#             */
/*   Updated: 2018/09/24 11:15:36 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "get_next_line.h"

char	**open_read(t_data *data)
{
	char	*line;
	char	*str;
	char	**ret;

	str = NULL;
	line = NULL;
	if ((data->fd = open(data->name, O_RDONLY)) == -1)
		ft_error("BAD READ\n");
	get_next_line(data->fd, &line);
	if (!line || ft_strlen(line) < 1)
		ft_error("BAD READ\n");
	str = ft_strdup(line);
	while (line != NULL)
	{
		free(line);
		str = ft_joinfree(str, "\n", 3);
		get_next_line(data->fd, &line);
		if (line != NULL)
			str = ft_joinfree(str, line, 3);
	}
	close(data->fd);
	ret = ft_strsplit(str, '\n');
	free(str);
	return (ret);
}

void	mamory_obj(t_data *data)
{
	if (!(data->lights = (t_light *)malloc(sizeof(t_light) * data->nb_lght)))
		ft_error("BAD MALLOC T_LIGHT\n");
	if (!(data->spheres = (t_sphere *)malloc(sizeof(t_sphere) * data->nb_sph)))
		ft_error("BAD MALLOC T_SPHERE\n");
	if (!(data->materials = (t_material *)malloc(sizeof(t_material) * data->nb_mtrl)))
		ft_error("BAD MALLOC T_MATERIAL\n");
	if (!(data->cylinder = (t_cylinder *)malloc(sizeof(t_cylinder) * data->nb_clndr)))
		ft_error("BAD MALLOC T_CYLINDER\n");
	if (!(data->cone = (t_cone *)malloc(sizeof(t_cone) * data->nb_cn)))
		ft_error("BAD MALLOC T_CONE\n");
	if (!(data->plane = (t_plane *)malloc(sizeof(t_plane) * data->nb_pln)))
		ft_error("BAD MALLOC T_PLANE\n");
}

int		else_record(t_data *data, char**str, int q)
{
	if (ft_strcmp(str[q], "materials") == 0)
	{
		add_par_mat_lg(data, str, q, 1);
		return (q + 4);
	}
	else if (ft_strcmp(str[q], "lights") == 0)
	{
		add_par_mat_lg(data, str, q, 2);
		return (q + 6);
	}
	else if (ft_strcmp(str[q], "plane") == 0)
	{
		add_par_plan(data, str, q);
		return (q + 7);
	}
	else if (ft_strcmp(str[q], "camera") == 0)
	{
		add_pos_cam(data, str, q);
		return (q + 6);
	}
	return (0);
}

int		record_obj(t_data *data, char **str, int q)
{
	if (ft_strcmp(str[q], "spheres") == 0)
	{
		add_par_spheres(data, str, q);
		return (q + 5);
	}
	else if (ft_strcmp(str[q], "cylinder") == 0)
	{
		add_par_cylinder(data, str, q);
		return (q + 8);
	}
	else if (ft_strcmp(str[q], "cone") == 0)
	{
		add_par_cone(data, str, q);
		return (q + 8);
	}
	else
		return (else_record(data, str, q));
	return (0);
}

void	read_pars(t_data *data)
{
	char **str;
	int q;
	str = open_read(data);
	q = 5;
	data->nb_sph = ft_atoi(str[0]);
	data->nb_lght = ft_atoi(str[1]);
	data->nb_mtrl = ft_atoi(str[2]);
	data->nb_clndr = ft_atoi(str[3]);
	data->nb_cn = ft_atoi(str[4]);
	data->nb_pln = ft_atoi(str[5]);
	check_str(data, str);
	mamory_obj(data);
	while (str[++q])
	{
		if (ft_isalpha(str[q][0]) == 1)
			q = record_obj(data, str, q);
		else
			ft_error("BAD MAP FOR OBJECT\n");
	}
	if ((data->sph != data->nb_sph) || (data->mtrl != data->nb_mtrl)
		|| (data->lght != data->nb_lght))
		ft_error("OBJECT BAD WRITTEN\n");
	q = -1;
	while (str[++q])
		free(str[q]);
	free(str);
}
