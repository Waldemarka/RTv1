/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 12:50:33 by vomelchu          #+#    #+#             */
/*   Updated: 2018/09/18 12:50:34 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#define EXIT (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)

void	init_all(t_data *data)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		ft_error("BAD INIT");
	if (!(data->win = SDL_CreateWindow("RTv1", 400, 400, WIDTH,
		HEIGHT, SDL_WINDOW_RESIZABLE)))
		ft_error("BAD CreateWindow");
	if (!(data->ren = SDL_CreateRenderer(data->win, -1, SDL_RENDERER_ACCELERATED
		| SDL_RENDERER_PRESENTVSYNC)))
		ft_error("BAD CreateRenderer");
	if (!(data->screen = SDL_CreateTexture(data->ren,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT)))
		ft_error("BAD CreateTexture");
}

void	put_color(t_data *data)
{
	int col;

	if (data->red * 255 > 255)
		data->red = 1;
	if (data->green * 255 > 255)
		data->green = 1;
	if (data->blue * 255 > 255)
		data->blue = 1;
	col = ((int)(data->red * 255) << 16) + ((int)(data->green * 255) << 8)
		+ ((int)(data->blue * 255));
	data->arr_col[data->y][data->x] = col;
}

void	for_render(t_data *data)
{
	SDL_Event	event;

	while (data->for_exit != 1)
	{
		SDL_UpdateTexture(data->screen, NULL, data->arr_col[0], WIDTH << 2);
		SDL_RenderCopy(data->ren, data->screen, NULL, NULL);
		SDL_RenderPresent(data->ren);
		draw(data);
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT || EXIT)
			{
				system("leaks RTV");
				data->for_exit = 1;
			}
	}
}

int		main(int argc, char **argv)
{
	t_data *data;

	if (argc == 2)
	{
		if (!(data = (t_data *)malloc(sizeof(t_data))))
			ft_error("BAD MALLOC T_DATA\n");
		data->name = argv[1];
		data->fd = open(data->name, O_DIRECTORY);
		if (data->fd >= 0)
			ft_error("NOT DIRECTORY");
		read_pars(data);
		init_all(data);
		for_render(data);
	}
	else
		ft_putstr("MORE THAN 2 ARGC\n");
	return (0);
}
