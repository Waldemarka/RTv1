/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 11:59:38 by vomelchu          #+#    #+#             */
/*   Updated: 2018/09/30 11:59:39 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_error(char *str)
{
	ft_putstr(str);
	exit(1);
}

double	make_double(char *str)
{
	double fir;
	double sec;
	int q;

	q = -1;
	fir = (double)ft_atoi(str);

	while (str[++q])
		if (str[q] == '.')
			sec = str[q + 1] - '0';
	if (fir < 0)
		return (fir - (sec / 10.0));
	return (fir + (sec / 10.0));
}

void	check_str(t_data *data, char **str)
{
	int q;
	int i;

	q = -1;
	i = 0;
	while (str[++q])
		if (ft_strcmp(str[q], "camera") == 0)
			i++;
	if (i != 1)
		ft_error("BAD NB camera");
	if (q != data->nb_sph * 6 + data->nb_mtrl * 5 + data->nb_lght * 7
		+ data->nb_clndr * 9 + data->nb_cn * 9 + data->nb_pln * 8 + 13)
		ft_error("BAD MAP");
}

void	add_pos_cam(t_data *data, char **str, int q)
{
	data->camera.pos.x = ft_atoi(str[q + 1]);
	data->camera.pos.y = ft_atoi(str[q + 2]);
	data->camera.pos.z = ft_atoi(str[q + 3]);
	data->camera.dir.x = ft_atoi(str[q + 4]);
	data->camera.dir.y = ft_atoi(str[q + 5]);
	data->camera.dir.z = ft_atoi(str[q + 6]);
}