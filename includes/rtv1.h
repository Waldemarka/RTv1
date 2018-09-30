/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 18:32:42 by vomelchu          #+#    #+#             */
/*   Updated: 2018/09/30 18:32:46 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# define WIDTH 800
# define HEIGHT 800

# include <unistd.h>
# include "../source/libft/includes/libft.h"
# include "../includes/get_next_line.h"
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <SDL_mixer.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

typedef	struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef struct		s_sphere
{
	t_vector		pos;
	double			radius;
	int				material;
}					t_sphere;

typedef struct		s_cylinder
{
	t_vector		pos;
	t_vector		dir;
	double			radius;
	int				material;
}					t_cylinder;

typedef struct		s_cone
{
	t_vector		pos;
	t_vector		dir;
	int				material;
	double			k;
}					t_cone;

typedef struct		s_plane
{
	t_vector		pos;
	t_vector		dir;
	int				material;
}					t_plane;

typedef struct		s_camera
{
	t_vector		pos;
	t_vector		dir;
}					t_camera;

typedef struct		s_ray
{
	t_vector		start;
	t_vector		dir;
}					t_ray;

typedef struct		s_color
{
	double			red;
	double			green;
	double			blue;
}					t_color;

typedef struct		s_material
{
	t_color			diffuse;
	double			reflection;
}					t_material;

typedef struct		s_light
{
	t_vector		pos;
	t_color			intensity;
}					t_light;

typedef struct		s_data
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*screen;
	t_ray			ray;
	t_vector		dist;
	t_vector		scaled;
	t_vector		new_start;
	t_vector		n;
	t_material		material;
	t_ray			ray_of_light;
	t_vector		temp;
	t_material		*materials;
	t_sphere		*spheres;
	t_light			*lights;
	t_cylinder		*cylinder;
	t_cone			*cone;
	t_plane			*plane;
	t_camera		camera;
	int				fd;
	char			*name;
	int				arr_col[HEIGHT][WIDTH];
	int				x;
	int				y;
	double			red;
	double			green;
	double			blue;
	int				level;
	double			coef;
	int				is_it_spher;
	double			discr;
	double			sqrt_discr;
	double			t;
	double			t_0;
	double			t_1;
	double			tmp;
	double			lamb;
	int				for_exit;
	int				nb_sph;
	int				nb_lght;
	int				nb_mtrl;
	int				nb_clndr;
	int				nb_cn;
	int				nb_pln;
	int				sph;
	int				lght;
	int				mtrl;
	int				clndr;
	int				cn;
	int				pln;
	int				nb_figur;
	int				i;
}					t_data;

void				ft_error(char *str);
char				*ft_joinfree(char *s1, char *s2, int j);
void				add_par_spheres(t_data *data, char **str, int q);
void				add_par_cylinder(t_data *data, char **str, int q);
void				add_par_cone(t_data *data, char **str, int q);
void				add_par_plan(t_data *data, char **str, int q);
void				add_pos_cam(t_data *data, char **str, int q);
void				add_par_mat_lg(t_data *data, char **str, int q, int check);
double				make_double(char *str);
void				check_str(t_data *data, char **str);
t_vector			vect_sub(t_vector *vec_1, t_vector *vec_2);
t_vector			vect_add(t_vector *vec_1, t_vector *vec_2);
t_vector			scale(t_vector *vec_1, double c);
double				vect_dot(t_vector *vec_1, t_vector *vec_2);
t_vector			vect_norm(t_vector *vec_1);
void				cos_sphe(t_data *data, t_ray *ray, int q);
void				cos_plane(t_data *data, t_ray *ray, int j);
void				cos_cyl(t_data *data, t_ray *ray, int q);
void				cos_cone(t_data *data, t_ray *ray, int q);
void				ini_date(t_data *data);
void				val_light(t_data *data);
t_vector			choose_nb_fig(t_data *data);
int					cont_draw(t_data *data);
void				put_color(t_data *data);
void				draw(t_data *data);
void				read_pars(t_data *data);

#endif
