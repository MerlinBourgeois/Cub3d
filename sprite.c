#include "cub3d.h"

void	find_ben(t_s *s)
{
	int i;
	int j;

	i = 0;
	while (i != s->map->map_lenght)
	{
		j = 0;
		while (j != s->map->map_len)
		{
			if (s->map->map[i][j] == 'O')
			{
				s->ben.x = i;
				s->ben.y = j;
 			}
			j++;
		}
		i++;
	}
}

float	distance_ben(t_s *s)
{
	float distance;

	distance = sqrt(pow(s->ben.x * - (s->player->x / 20), 2) + pow(s->ben.y - (s->player->y / 20), 2));
	return (distance);
}

void	draw_texture_color(t_s *s, int x, int y)
{
	t_xpm *texture = &s->xpm[4];
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return ;
	int color = *(unsigned int *)(texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8)));
	if ((unsigned int)color != 0xff000000)
	{
		my_mlx_pixel_put(s->img, x, y, color);
	}
}

void resize_sprite(float distance, int *sprite_width, int *sprite_height, t_s *s)
{
    float factor = distance / 4.0;
    *sprite_width = (int)(*sprite_width * factor);
    *sprite_height = (int)(*sprite_height * factor);
	s->xpm[4].height += *sprite_width;
	s->xpm[4].width += *sprite_height;
}

void draw_ben(t_s *s, int sprite_x, int sprite_y)
{
    t_xpm *texture = &s->xpm[4];
    int x;
    int y;

    y = 0;
	int sprite_height = s->xpm[4].height;
	int sprite_width = s->xpm[4].width;
	float distance = distance_ben(s);
	resize_sprite(distance, &sprite_width, &sprite_height, s);
    while (y != texture->height)
    {
        x = 0;
        while (x != texture->width)
        {
            int color = *(unsigned int *)(texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8)));
            if ((unsigned int)color != 0xff000000)
            {
                my_mlx_pixel_put(s->img, x + sprite_x, y + sprite_y, color);
            }
            x++;
        }
        y++;
    }
}

// void	update_ben(t_s *s)
// {
// 	find_ben(s);
// 	int sprite_height = s->xpm[4].height;
// 	int sprite_width = s->xpm[4].width;
// 	float distance = distance_ben(s);
// 	resize_sprite(distance, &sprite_width, &sprite_height, s);
// }