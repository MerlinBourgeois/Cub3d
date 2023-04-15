#include "cub3d.h"

t_xpm textures_init(t_s *s, char *path)
{
    t_xpm sprite;
    sprite.img = mlx_xpm_file_to_image(s->p->mlx, path, &sprite.width, &sprite.height);
    sprite.addr = mlx_get_data_addr(sprite.img, &sprite.bits_per_pixel, &sprite.line_length, &sprite.endian);
    return (sprite);
}

//fonction d'aatribution de la couleur du pixel sur la texture

unsigned int get_wall_face_color(t_s *s, char wall_face, int x, int y)
{
    int texture_idx = -1;

	if (wall_face == 'N')
	{
		texture_idx = 0;
	}
	else if (wall_face == 'S')
	{
		texture_idx = 1;
	}
	else if (wall_face == 'E')
	{
		texture_idx = 2;
	}
	else if (wall_face == 'W')
	{
		texture_idx = 3;
	}
    else if (texture_idx == -1) 
		return 0xFFFFFF;
    t_xpm *texture = &s->xpm[texture_idx];
    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height) 
		return 0;
    return *(unsigned int *)(texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8)));
}

//fonction de déplacement de la caméra

camera_t *updateCameraPosition(camera_t *camera, float dx, float dy)
{
    camera->pos.x += camera->dir.x * dy + camera->dir.y * dx;
    camera->pos.y += camera->dir.y * dy - camera->dir.x * dx;
    return (camera);
}

//fonction de correction de fisheye

float getCorrectedDistance(float distance, float angle)
{
    float correctedDistance = distance * cos(angle);
    return correctedDistance;
}

//fonction génerale du raycast

void render(camera_t *camera, char **map, int mapWidth, int mapHeight, t_s *s)
{
    const float inv_num_rays = 1.0f / NUM_RAYS;
    const int half_screen_height = SCREEN_HEIGHT / 2;

    const float fov_offset = FOV / 2.0;
    const float fov_times_inv_num_rays = FOV * inv_num_rays;

    for (int i = 0; i < NUM_RAYS; i++)
    {
        float rayAngle = (camera->dir.x - fov_offset) + ((float)i * fov_times_inv_num_rays);
        ray_t ray = { 0 };
        int mapX = (int)camera->pos.x;
        int mapY = (int)camera->pos.y;
        float eyeX = sin(rayAngle);
        float eyeY = cos(rayAngle);
        float deltaDistX = fabs(1 / eyeX);
        float deltaDistY = fabs(1 / eyeY);
        float sideDistX;
        float sideDistY;
        int stepX;
        int stepY;
        if (eyeX < 0)
        {
            stepX = -1;
            sideDistX = (camera->pos.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - camera->pos.x) * deltaDistX;
        }
        if (eyeY < 0)
        {
            stepY = -1;
            sideDistY = (camera->pos.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - camera->pos.y) * deltaDistY;
        }
        int hit = 0;
        while (!hit)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                if (stepX == 1)
                    ray.wallFace = 'E';
                else
                    ray.wallFace = 'W';
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                if (stepY == 1)
                    ray.wallFace = 'N';
                else
                    ray.wallFace = 'S';
            }
            if (map[mapY][mapX] == '1')
            {
                hit = 1;
            }
        }

        float perpWallDist;
        if (ray.wallFace == 'E' || ray.wallFace == 'W')
        {
            perpWallDist = (mapX - camera->pos.x + (1 - stepX) / 2) / eyeX;
        }
        else
        {
            perpWallDist = (mapY - camera->pos.y + (1 - stepY) / 2) / eyeY;
        }
        ray.distance = perpWallDist;
        int wallHeight = (int)((float)SCREEN_HEIGHT / getCorrectedDistance(ray.distance, rayAngle - camera->dir.x));
        int halfWallHeight = wallHeight / 2;
        int drawStart = -halfWallHeight + half_screen_height;
        int drawEnd = halfWallHeight + half_screen_height;
        int lineHeight = drawEnd - drawStart;
        float wallX;
        if (ray.wallFace == 'N' || ray.wallFace == 'S')
            wallX = camera->pos.x + perpWallDist * eyeX;
        else
            wallX = camera->pos.y + perpWallDist * eyeY;

        wallX -= floor(wallX);

        int texNum;
        if (ray.wallFace == 'N')
            texNum = 0;
        else if (ray.wallFace == 'S')
            texNum = 1;
        else if (ray.wallFace == 'W')
            texNum = 2;
        else // ray.wallFace == 'E'
            texNum = 3;

        int texX = (int)(wallX * (float)s->xpm[texNum].width);
        if (((ray.wallFace == 'N' || ray.wallFace == 'S') && eyeX > 0) ||
            ((ray.wallFace == 'W' || ray.wallFace == 'E') && eyeY < 0))
            texX = s->xpm[texNum].width - texX - 1;

        float step = 1.0 * s->xpm[texNum].height / lineHeight;
        float texPos = (drawStart - half_screen_height + lineHeight / 2) * step;

        for (int j = drawStart; j < drawEnd; j++)
        {
            int texY = (int)texPos & (s->xpm[texNum].height - 1);
            texPos += step;
            s->p->color = get_wall_face_color(s, ray.wallFace, texX, texY);
            my_mlx_pixel_put(s->img, i, j, s->p->color);
        }
    }
}


//fonction pour mettre les variable de t_s dans les variables spécifiques au raycast

void	cast_rays(t_s *s)
{
	int mapWidth = s->map->map_len;
	int mapHeight = s->map->map_lenght;
	camera_t camera = { { s->player->y / TILE_SIZE, s->player->x / TILE_SIZE }, { s->player->player_angle, -1.0 } };
	render(&camera, s->map->map, mapWidth, mapHeight, s);
}
