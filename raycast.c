#include "cub3d.h"

//fonction de tracage de ligne

void	draw_line(t_s *s, int x0, int y0, int x1, int y1)
{
  int dx =  abs (x1 - x0);
  int sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0);
  int sy = y0 < y1 ? 1 : -1; 
  int err = dx + dy, e2;
 
  for (;;)
  {
	if (x0 >= 0 && x0 < SCREEN_WIDTH && y0 >= 0 && y0 < SCREEN_HEIGHT)
		my_mlx_pixel_put(s->img, x0, y0, s->p->color);
    if (x0 == x1 && y0 == y1) 
		break;
    e2 = 2 * err;
    if (e2 >= dy)
	{
		err += dy;
		x0 += sx;
	}
    if (e2 <= dx)
	{
		err += dx;
		y0 += sy;
	}
  }
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

//fonction d'attribution de couleur en fonction de la face

void setWallFaceColor(t_s *s, char wallFace)
{
    int color;
    if (wallFace == 'N')
    	color = 0xFF0000;
	else if (wallFace == 'S')
		color = 0x0000FF;
	else if (wallFace == 'E')
		color = 0x00FF00;
	else if (wallFace == 'W')
		color = 0xFFFF00;
	else
		color = 0xFFFFFF;
    s->p->color = color;
}

//fonction génerale du raycast

void render(camera_t *camera, char **map, int mapWidth, int mapHeight, t_s *s)
{
    float rayAngle;
    for (int i = 0; i < NUM_RAYS; i++)
	{
        rayAngle = (camera->dir.x - FOV / 2.0) + ((float)i / NUM_RAYS) * FOV;
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
        int drawStart = -wallHeight / 2 + SCREEN_HEIGHT / 2;
        int drawEnd = wallHeight / 2 + SCREEN_HEIGHT / 2;
        setWallFaceColor(s, ray.wallFace);
		draw_line(s, i, drawStart, i, drawEnd);
    }
}

//fonction pour mettre les variable de t_s dans les variables spécifiques au raycast

void	cast_rays(t_s *s)
{
	int mapWidth = s->map->map_len;
	int mapHeight = s->map->map_lenght;
	camera_t camera = { { s->player->y / 20, s->player->x / 20 }, { s->player->player_angle, -1.0 } };
	render(&camera, s->map->map, mapWidth, mapHeight, s);
}
