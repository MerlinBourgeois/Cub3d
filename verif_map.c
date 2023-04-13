/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlinbourgeois <merlinbourgeois@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 06:46:57 by merlinbourg       #+#    #+#             */
/*   Updated: 2023/03/14 00:36:38 by merlinbourg      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//fonction d'impression de la map (a supprimer)

void	ft_print_map(t_map *map)
{
	int	i;

	i = 0;
	printf("%s -->%s\n", "NO", map->north_texture);
	printf("%s -->%s\n", "SO", map->south_texture);
	printf("%s -->%s\n", "WE", map->west_texture);
	printf("%s -->%s\n", "EA", map->east_texture);
	printf("floor / 1 : %d, 2 : %d, 3 : %d\n",
		(unsigned char)map->floor_color, (unsigned char)(map->floor_color >> 8),
		(unsigned char)(map->floor_color >> 16));
	printf("Ceiling / 1 : %d, 2 : %d, 3 : %d\n",
		(unsigned char)map->Ceiling_color,
		(unsigned char)(map->Ceiling_color >> 8),
		(unsigned char)(map->Ceiling_color >> 16));
	while (i < map->map_lenght)
	{
		printf("%s\n", map->map[i]);
		i++;
	}
}

//fonction de vérification de la présence du joueur sur la carte

int	ft_is_player(char **map, t_map *s)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'W' || map[i][j] == 'E'
			|| map[i][j] == 'S' || map[i][j] == 'N')
			{
				s->def_x = i * 20;
				s->def_y = j * 20;
				s->def_angle = map[i][j];
				player++;
			}
			j++;
		}
		i++;
	}
	return (player);
}

//fonction pour retirer les espaces en fin de ligne

char	**ft_without_spaces(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = ft_strlen(map[i]) - 1;
		while (map[i][j] == ' ')
		{
			map[i][j] = '\0';
			j--;
		}
		i++;
	}
	return (map);
}

//fonction pour retirer les newline en fin de ligne

char	**ft_without_newline(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			j++;
		}
		if (map[i][ft_strlen(map[i]) - 1] == '\n')
			map[i][j - 1] = '\0';
		i++;
	}
	return (map);
}

//fonction pour vérifier que les carracteres présents sur la map soient les bons

void	ft_verif_char_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	map->map = ft_without_newline(map->map);
	map->map = ft_without_spaces(map->map);
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] != '1' && map->map[i][j] != '0' && map->map[i][j]
			!= ' ' && map->map[i][j] != 'W' && map->map[i][j]
			!= 'E' && map->map[i][j] != 'S' && map->map[i][j] != 'N' && map->map[i][j] != 'O')
				ft_error(CHAR_ERROR);
			j++;
		}
		i++;
	}
	if (ft_is_player(map->map, map) != 1)
		ft_error(BAD_PLAYER_ERROR);
	if (!ft_verif_map_shape(map))
		ft_error(MAP_LAYOUT_ERROR);
	space_to_one(map);
	map->map_len = ft_strlen(map->map[0]);
	ft_print_map(map);
}
