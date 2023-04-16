/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlinbourgeois <merlinbourgeois@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:15:42 by merlinbourg       #+#    #+#             */
/*   Updated: 2023/04/16 11:01:44 by merlinbourg      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long long getCurrentMicroseconds() {
    struct timespec currentTime;
    clock_gettime(CLOCK_MONOTONIC, &currentTime);
    return currentTime.tv_sec * 1e6 + currentTime.tv_nsec / 1e3;
}

void	load_textures(t_s *s)
{
	s->xpm = malloc(4 * sizeof(t_xpm));
	s->map->north_texture = "backroom_texture.xpm";
	s->map->south_texture = "wall.xpm";
	s->map->east_texture = "ground.xpm";
	s->map->west_texture = "backroom_texture.xpm";
	s->xpm[0] = textures_init(s, s->map->north_texture);
	s->xpm[1] = textures_init(s, s->map->south_texture);
	s->xpm[2] = textures_init(s, s->map->east_texture);
	s->xpm[3] = textures_init(s, s->map->west_texture);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > SCREEN_WIDTH || y > SCREEN_HEIGHT - 1)
	{
		//printf("tu fais quoi frero?\n");
		return ;
	}
	//printf("pixel x : %d\npixel y : %d\n", x, y);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / BITS_PER_BYTE));
	//printf("adrr : %p\n", dst);
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
	float x_tile_size;
	float y_tile_size;

	x = 0;
	y = 0;
	yo = 0;
	xo = 0;
	x_tile_size = s->player->x / TILE_SIZE;
	y_tile_size = s->player->y / TILE_SIZE;
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
			draw_square_minimap(s, (y - x_tile_size) * TILE_SIZE + s->map->def_x, (x - y_tile_size)* TILE_SIZE + s->map->def_y, TILE_SIZE, TILE_SIZE);
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
			draw_big_line(s, (co->x[i] - y_tile_size)* TILE_SIZE + 10 + s->map->def_y , (co->y[i] - x_tile_size) * TILE_SIZE + 10 + s->map->def_x, (co->x[i + 1] - y_tile_size) * TILE_SIZE + 10 + s->map->def_y, (co->y[i + 1] - x_tile_size) * TILE_SIZE + 10 + s->map->def_x, 8);
		}
		if (i == 0)
		{
			s->p->color = 0xaa8085;
			draw_square_minimap(s, (co->y[i] - x_tile_size) * TILE_SIZE + s->map->def_x, (co->x[i] - y_tile_size) * TILE_SIZE + s->map->def_y, TILE_SIZE, TILE_SIZE);
		}
		i++;
	}
	free(co->x);
	free(co->y);
	free(co);
	int j;

	i = 0;
	if (s->map->map[(int)x_tile_size][(int)y_tile_size] == '0')
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
		s->map->map[(int)(x_tile_size)][(int)(y_tile_size)] = 'N';
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
	while (i < SCREEN_HEIGHT_1)
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

int is_wall(char **map, float y, float x, int mapWidth, int mapHeight)
{
    int intX = (int)floorf(x);
    int intY = (int)floorf(y);

	if (map[intY][intX] == '1')
	{
		return (1);
	}
	else
		return (0);
}

int	relase_key_hook(int	keycode, t_s *s)
{
    if (keycode == EAST)
        s->key_states.east = false;
    else if (keycode == WEST)
        s->key_states.west = false;
    else if (keycode == NORTH)
        s->key_states.north = false;
    else if (keycode == SOUTH)
        s->key_states.south = false;
    return (0);
}

int key_hook(int keycode, t_s *s)
{
    if (keycode == 53)
        exit(0);
    else if (keycode == EAST)
        s->key_states.east = true;
    else if (keycode == WEST)
        s->key_states.west = true;
    else if (keycode == NORTH)
        s->key_states.north = true;
    else if (keycode == SOUTH)
        s->key_states.south = true;
    return (0);
}

void update_player_movement(t_s *s, double delta_time)
{
    if (s->key_states.east == true)
    {
        s->player->player_angle -= PI / 60 * delta_time * 1.0;
        if (s->player->player_angle < 0)
        {
            s->player->player_angle = 2 * PI;
        }
        s->player->delta_x = (cos(s->player->player_angle) * 2);
        s->player->delta_y = (sin(s->player->player_angle) * 2);
    }

    if (s->key_states.west == true)
    {
        s->player->player_angle += PI / 60 * delta_time * 1.0;
        if (s->player->player_angle > 2 * PI)
        {
            s->player->player_angle = 0;
        }
        s->player->delta_x = (cos(s->player->player_angle) * 2);
        s->player->delta_y = (sin(s->player->player_angle) * 2);
    }
    if (s->key_states.north == true)
    {
        if (!is_wall(s->map->map, ((s->player->x + s->player->delta_x) / 20 + COLLISION_MARGIN), ((s->player->y + s->player->delta_y) / 20 + COLLISION_MARGIN), s->map->map_len, s->map->map_lenght))
        {
            s->player->x += s->player->delta_x / 2;
            s->player->y += s->player->delta_y / 2;
        }
    }
    if (s->key_states.south == true)
    {
        if (!is_wall(s->map->map, ((s->player->x - s->player->delta_x) / 20 - COLLISION_MARGIN), ((s->player->y - s->player->delta_y) / 20 - COLLISION_MARGIN), s->map->map_len, s->map->map_lenght))
        {
            s->player->x -= s->player->delta_x / 2;
            s->player->y -= s->player->delta_y / 2;
        }
    }
}


const int NUM_FRAMES_TO_MEASURE = 10;
int frameCounter = 0;
long long elapsedTime;
double fps = 0;

int	paint_frame(t_s *s)
{
	//clear_window(s);
	update_player_movement(s, 0.5);
	s->player->delta_x = cos(s->player->player_angle) * 5;
	s->player->delta_y = sin(s->player->player_angle) * 5;
	display_ceiling_floor(*s->img, s->p, s->map);
	cast_rays(s);
	draw_map_2d(s);
	mlx_put_image_to_window(s->p->mlx, s->p->mlx_win, s->img->img, 0, 0);
	frameCounter++;
	if (frameCounter >= NUM_FRAMES_TO_MEASURE) {
		elapsedTime = getCurrentMicroseconds() - s->start_time;
		fps = (double)frameCounter / (elapsedTime / 1e6);
		// Réinitialiser le compteur et le temps de départ pour la prochaine mesure
		frameCounter = 0;
		s->start_time = getCurrentMicroseconds();
	}
	mlx_string_put(s->p->mlx, s->p->mlx_win, SCREEN_WIDTH - 40, SCREEN_HEIGHT - 40, 0xFFFF00FF, ft_itoa((int)fps));
	return (0);
}

void	display_window(t_map *map)
{
	t_s s;

	s.map = map;
	
	ft_allocate_struct(&s);
	s.player->x = map->def_x;
	s.player->y = map->def_y;
	s.player->player_angle = M_PI_2;
	printf("x : %f, y : %f\n", s.player->x, s.player->y);
	if (s.map->map_len > s.map->map_lenght)
	{
		s.map->map_max = s.map->map_len;
	}
	else
		s.map->map_max = s.map->map_lenght;
	s.key_states.east = false;
    s.key_states.west = false;
    s.key_states.north = false;
    s.key_states.south = false;
	s.map->map_line = concatenate_string_array(map->map, map->map_len);
	s.p->mlx = mlx_init();
	s.p->mlx_win = mlx_new_window(s.p->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, TITLE_SCREEN);
	s.img->img = mlx_new_image(s.p->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	s.img->addr = mlx_get_data_addr(s.img->img, &s.img->bits_per_pixel, &s.img->line_length,
								&s.img->endian);

							
	s.start_time = getCurrentMicroseconds();
	
	load_textures(&s);
	mlx_hook(s.p->mlx_win, 3, 1L<<0, relase_key_hook, &s);
	mlx_hook(s.p->mlx_win, 2, 1L<<1, key_hook, &s);
	mlx_loop_hook(s.p->mlx, paint_frame, &s);
	mlx_loop(s.p->mlx);
}
