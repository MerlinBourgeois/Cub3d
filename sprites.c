#include "cub3d.h"

t_sprite sprite_init(t_s *s, char *path)
{
    t_sprite sprite;
    sprite.img = mlx_xpm_file_to_image(s->p->mlx, path, &sprite.width, &sprite.height);
    sprite.addr = mlx_get_data_addr(sprite.img, &sprite.bits_per_pixel, &sprite.line_length, &sprite.endian);
    return sprite;
}
