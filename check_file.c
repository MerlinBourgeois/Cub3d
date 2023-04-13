/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlinbourgeois <merlinbourgeois@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:16:18 by merlinbourg       #+#    #+#             */
/*   Updated: 2023/03/12 20:40:15 by merlinbourg      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//fonction d'allocation du tableau de string de la map

char	**ft_allocate_table(int fd, t_map *map_struct,
	int line_pos, char **argv)
{
	int		i;
	char	*line;

	i = 0;
	close(fd);
	fd = open(argv[1], O_RDONLY);
	map_struct->map = malloc((map_struct->map_lenght + 1) * sizeof(char *));
	if (!map_struct->map)
		exit(EXIT_FAILURE);
	while (i != line_pos - 1)
	{
		line = get_next_line(fd);
		free(line);
		i++;
	}
	i = 0;
	map_struct->map[i] = line;
	while (i != map_struct->map_lenght + 1)
	{
		line = get_next_line(fd);
		map_struct->map[i] = line;
		i++;
	}
	return (map_struct->map);
}

//fonction pour lancer la vérification de la map

t_map	check_map(int fd, char **argv)
{
	t_map	map;

	map.map = ft_allocate_table(fd, &map,
			ft_put_file_table(fd, argv, &map), argv);
	ft_verif_char_map(&map);
	return (map);
}
