/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_modifier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlinbourgeois <merlinbourgeois@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:26:19 by merlinbourg       #+#    #+#             */
/*   Updated: 2023/04/16 11:58:17 by merlinbourg      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Ce fichier sert a parser la map en changant les espaces contenus dans la map en 1

void	space_to_one(t_map *map)
{
	int i;
	int j;
	int long_line_len;

	i = 0;
	long_line_len = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
			j++;
		if (j > long_line_len)
			long_line_len = j;
		i++;
	}
	i = 0;
	while (map->map[i])
	{
		// j = ft_strlen(map->map[i]);
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == ' ')
				map->map[i][j] = '1';
			j++;
		}
		map->map[i] = ft_realloc(map->map[i], long_line_len + 1);
		while (j < long_line_len)
		{
			map->map[i][j] = '1';
			j++;
		}
		map->map[i][j] = 0;
		i++;
	}
	
}