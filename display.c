/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlinbourgeois <merlinbourgeois@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:15:42 by merlinbourg       #+#    #+#             */
/*   Updated: 2023/04/13 01:39:37 by merlinbourg      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int point_in_circle(double x, double y, double cx, double cy, double r)
{
    double distance = sqrt(pow(x - cx, 2) + pow(y - cy, 2));
    if (distance <= r)
	{
        return 1; // Le point est dans le cercle
    }
	else
	{
        return 0; // Le point est en dehors du cercle
    }
}

void	draw_line_minimap(t_s *s, int x0, int y0, int x1, int y1)
{
  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
  int err = dx + dy, e2;
 
  for (;;)
  {
	if (x0 >= 0 && x0 < SCREEN_WIDTH && y0 >= 0 && y0 < SCREEN_HEIGHT && point_in_circle(x0, y0, MINIMAP_X, MINIMAP_Y, 150))
		my_mlx_pixel_put(s->img, x0, y0, s->p->color);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; }
    if (e2 <= dx) { err += dx; y0 += sy; }
  }
}

void	draw_big_line(t_s *s, int x0, int y0, int x1, int y1, int thick)
{
	int above;
	int i;

	above = thick / 2;
	i = 0;
	while (i != above)
	{
		draw_line_minimap(s, x0 + i, y0 + i, x1 + i, y1 + i);
		draw_line_minimap(s, x0 - i, y0 - i, x1 - i, y1 - i);
		i++;
	}
}

void draw_circle(t_s *s, int x0, int y0, int radius, int color)
{
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
            {
				my_mlx_pixel_put(s->img, x0 + x, y0 + y, s->p->color);
            }
        }
    }
}

void draw_square_minimap(t_s *s, int x, int y, int size_x, int size_y)
{
    // Vérification que les coordonnées ne débordent pas de l'écran
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x + size_x >= SCREEN_HEIGHT) size_x = SCREEN_HEIGHT - x - 1;
    if (y + size_y >= SCREEN_WIDTH) size_y = SCREEN_WIDTH - y - 1;

    int i;
    int j;

    // Boucle pour dessiner chaque pixel du carré
    i = y;
    while (i <= y + size_y)
    {
        j = x;
        while (j <= x + size_x)
        {
            // Vérification que les coordonnées ne débordent pas de l'écran
            if (i >= 0 && i < SCREEN_WIDTH && j >= 0 && j < SCREEN_HEIGHT && point_in_circle(i, j, MINIMAP_X, MINIMAP_Y, 150))
            {
                my_mlx_pixel_put(s->img, i, j, s->p->color);
            }
            j++;
        }
        i++;
    }
}

char	*concatenate_string_array(char **map, int len)
{
	char	*map_line;
	int		i;

	i = 1;
	map_line = ft_strdup(map[0]);
	while (map[i])
	{
		map_line = ft_strjoin(map_line, map[i]);
		i++;
	}
	map_line[i * len] = '\0';
	return(map_line);
}

float	ft_square(float f)
{
	return(f * f);
}

float	distance(float y1, float x1, float y2, float x2)
{
	return (sqrt((y1 - y2) * (y1 - y2) + (x1 - x2) * (x1 - x2)));
}

void	clear_window(t_s *s)
{
	int i;
	int j;

	i = 0;
	while (i < SCREEN_HEIGHT)
	{
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(s->img, j, i, 0x00000000);
			j++;
		}
		i++;
	}
}

void	better_minimap(t_s *s)
{
	int	x;
	int	y;
	int	xo;
	int	yo;
	int i;
	int fill_minimap_x;
	int fill_minimap_y;
	t_path_return *co;

	x = 0;
	y = 0;
	yo = 0;
	xo = 0;
	s->map->def_y = MINIMAP_X;
	s->map->def_x = MINIMAP_Y;
	//BONUS fonction d'appel du path finding

	fill_minimap_x = 0;
	while (fill_minimap_x <= 350)
	{
		fill_minimap_y = 0;
		while (fill_minimap_y <= 350)
		{
			if (point_in_circle(fill_minimap_x, fill_minimap_y, MINIMAP_X, MINIMAP_Y, 150))
				my_mlx_pixel_put(s->img, fill_minimap_x, fill_minimap_y, 0x4e2823);
			else if (point_in_circle(fill_minimap_x, fill_minimap_y, MINIMAP_X, MINIMAP_Y, 160))
				my_mlx_pixel_put(s->img, fill_minimap_x, fill_minimap_y, 0x182029);
			fill_minimap_y++;
		}
		fill_minimap_x++;
	}
	co = get_path_finding_input(s->map->map, s->map->map_len, s->map->map_lenght);
	while (y < s->map->map_lenght)
	{
		x = 0;
		while (x < s->map->map_len)
		{
			if (s->map->map[y][x] == '1')
			{
				s->p->color = 0x4e2823;
			}
			else if (s->map->map[y][x] == '0')
			{
				s->p->color = 0x397a41;
			}
			//BONUS colorier la sortie en vert
			else if (s->map->map[y][x] == 'O')
			{
				s->p->color = 0xb96f2c;
			}
			else if (s->map->map[y][x] == 'E' || s->map->map[y][x] == 'N' || s->map->map[y][x] == 'S' || s->map->map[y][x] == 'W')
			{
				s->p->color = 0x629cc5;
			}
			draw_square_minimap(s, (y - (s->player->x)/ 20) * 20 + s->map->def_x, (x - (s->player->y) / 20)* 20 + s->map->def_y, 20, 20);
			x++;
		}
		y++;
	}
	i = 0;
	//BONUS d'affichage du path_finding sur la map
	while(co && i != co->moves)
	{
		//BONUS affichage du joueur en bleu
		s->p->color = 0x333333;
		if (i != co->moves - 1)
		{
			draw_big_line(s, (co->x[i] - s->player->y / 20)* 20 + 10 + s->map->def_y , (co->y[i] - s->player->x / 20) * 20 + 10 + s->map->def_x, (co->x[i + 1] - s->player->y / 20) * 20 + 10 + s->map->def_y, (co->y[i + 1] - s->player->x / 20) * 20 + 10 + s->map->def_x, 8);
		}
		if (i == 0)
		{
			s->p->color = 0xaa8085;
			draw_square_minimap(s, (co->y[i] - s->player->x / 20) * 20 + s->map->def_x, (co->x[i] - s->player->y / 20) * 20 + s->map->def_y, 20, 20);
		}
		i++;
	}
	free(co->x);
	free(co->y);
	free(co);
	int j;

	i = 0;
	if (s->map->map[(int)(s->player->x / 20)][(int)(s->player->y / 20)] == '0')
	{
		while (i != s->map->map_lenght)
		{
			j = 0;
			while (j != s->map->map_len)
			{
				if (s->map->map[i][j] == 'W' || s->map->map[i][j] == 'E' || s->map->map[i][j] == 'S' || s->map->map[i][j] == 'N')
					s->map->map[i][j] = '0';
				j++;
			}
			i++;
		}
		s->map->map[(int)(s->player->x / 20)][(int)(s->player->y / 20)] = 'N';
	}
	s->p->color = 0x0FFFFF0;
	draw_circle(s, (s->map->def_x), (s->map->def_y), 5, 0xFFFFFFFF);
	draw_line_minimap(s, (s->map->def_y), (s->map->def_x), (s->map->def_y) + s->player->delta_y * 5, (s->map->def_x) + s->player->delta_x * 5);
}

void	draw_map_2d(t_s *s)
{
	better_minimap(s);
}

void	display_ceiling_floor(t_data img, void *mlx, t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < SCREEN_HEIGHT / 2)
	{
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(&img, j, i, map->Ceiling_color);
			j++;
		}
		i++;
	}
	while (i < SCREEN_HEIGHT)
	{
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(&img, j, i, map->floor_color);
			j++;
		}
		i++;
	}
}

void	ft_allocate_struct(t_s *s)
{
	s->p = malloc(1 * sizeof(t_mlx));
	if (!s->p)
		exit(EXIT_FAILURE);
	s->img = malloc(1 * sizeof(t_data));
	if (!s->img)
	{
		free(s->p);
		exit(EXIT_FAILURE);
	}
	s->player = malloc(1 * sizeof(t_player));
	if (!s->player)
	{
		free(s->p);
		free(s->img);
		exit(EXIT_FAILURE);
	}
}

int	key_hook(int keycode, t_s *s)
{
	if (keycode == 53)
		exit(0);
	if (keycode == EAST)
	{
		s->player->player_angle -= PI / 30;
		if (s->player->player_angle < 0)
		{
			s->player->player_angle = 2 * PI;
		}
		s->player->delta_x = (cos(s->player->player_angle) * 5);
		s->player->delta_y = (sin(s->player->player_angle) * 5);

	}
	if (keycode == WEST)
	{
		s->player->player_angle += PI / 30;
		if (s->player->player_angle > 2 * PI)
		{
			s->player->player_angle = 0;
		}
		s->player->delta_x = (cos(s->player->player_angle) * 5);
		s->player->delta_y = (sin(s->player->player_angle) * 5);
	}
	if (keycode == NORTH)
	{
		s->player->x += s->player->delta_x;
		s->player->y += s->player->delta_y;
	}
	if (keycode == SOUTH)
	{
		s->player->x -= s->player->delta_x;
		s->player->y -= s->player->delta_y;
	}
	return (0);
}

int	paint_frame(t_s *s)
{
	clear_window(s);
	s->player->delta_x = cos(s->player->player_angle) * 5;
	s->player->delta_y = sin(s->player->player_angle) * 5;
	display_ceiling_floor(*s->img, s->p, s->map);
	cast_rays(s);
	draw_map_2d(s);
	mlx_put_image_to_window(s->p->mlx, s->p->mlx_win, s->img->img, 0, 0);
	return (0);
}

void	display_window(t_map *map)
{
	t_s s;

	s.map = map;
	
	ft_allocate_struct(&s);
	s.player->x = map->def_x;
	s.player->y = map->def_y;
	s.player->player_angle = PI / 2;
	printf("x : %f, y : %f\n", s.player->x, s.player->y);
	if (s.map->map_len > s.map->map_lenght)
	{
		s.map->map_max = s.map->map_len;
	}
	else
		s.map->map_max = s.map->map_lenght;
	s.map->map_line = concatenate_string_array(map->map, map->map_len);
	s.p->mlx = mlx_init();
	s.p->mlx_win = mlx_new_window(s.p->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, TITLE_SCREEN);
	s.img->img = mlx_new_image(s.p->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	s.img->addr = mlx_get_data_addr(s.img->img, &s.img->bits_per_pixel, &s.img->line_length,
								&s.img->endian);
	mlx_hook(s.p->mlx_win, 2, 1L<<0, key_hook, &s);
	mlx_loop_hook(s.p->mlx, paint_frame, &s);
	mlx_loop(s.p->mlx);
}
