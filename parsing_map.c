/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlinbourgeois <merlinbourgeois@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:49:47 by merlinbourg       #+#    #+#             */
/*   Updated: 2023/04/24 17:34:12 by merlinbourg      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Fichier contenant le découpage d'une fonction servant 
//a parser le contenu du fichier .cub et le mettre
//dans la structure

void	ft_put_file_table5(t_verif *verif, t_map *map_struct, int fd)
{
	if (verif->instruct != 6)
		ft_error(BAD_FILE);
	verif->line = get_next_line(fd);
	verif->line_pos++;
	while (ft_strncmp(verif->line, "\n", 1) == 0)
	{
		free(verif->line);
		verif->line = get_next_line(fd);
		verif->line_pos++;
	}
	while (verif->line != NULL)
	{
		free(verif->line);
		verif->map_pos++;
		verif->line = get_next_line(fd);
	}
	free(verif->line);
	map_struct->map_lenght = verif->map_pos;
}

void	ft_put_file_table4(t_verif *verif, t_map *map_struct)
{
	if (ft_strncmp(verif->line, "C ", 2) == 0)
	{
		verif->indic = 0;
		verif->tmp = ft_split(ft_strrchr(verif->line, ' ') + 1, ',');
		while (verif->tmp[verif->indic] != NULL)
		{
			map_struct->Ceiling_color |= (ft_atoi(verif->tmp[verif->indic])
					<< (verif->indic * 8));
			verif->indic++;
		}
		free_tab(verif->tmp);
		verif->instruct++;
	}
}

int	ft_find_my_str(char *s, int i)
{
	int j;

	j = 0;
	while (j != i)
	{
		if (s[j] && s[j + 1] && s[j] == '.' && s[j + 1] == '/')
			return(1);
		j++;
	}
	return (0);
}

void	ft_put_file_table3(t_verif *verif, t_map *map_struct)
{
	if (ft_strncmp(verif->line, "EA ", 3) == 0)
	{
		if (!ft_find_my_str(verif->line, ft_strlen(verif->line)))
			ft_error("Bad texture name");
		map_struct->east_texture = ft_strnstr(verif->line,
				"./", ft_strlen(verif->line));
		map_struct->east_texture[ft_strlen(map_struct->east_texture)
			- 1] = '\0';
		verif->instruct++;
	}
	else if (ft_strncmp(verif->line, "F ", 2) == 0)
	{
		verif->indic = 0;
		verif->tmp = ft_split(ft_strrchr(verif->line, ' ') + 1, ',');
		while (verif->tmp[verif->indic] != NULL)
		{
			map_struct->floor_color |= (ft_atoi(verif->tmp[verif->indic])
					<< (verif->indic * 8));
			verif->indic++;
		}
		free_tab(verif->tmp);
		verif->instruct++;
	}
}

void	ft_put_file_table2(t_verif *verif, t_map *map_struct)
{
	int i;

	i = 0;
	if (ft_strncmp(verif->line, "NO ", 3) == 0)
	{
		if (!ft_find_my_str(verif->line, ft_strlen(verif->line)))
			ft_error("Bad texture name");
		map_struct->north_texture = ft_strnstr(verif->line, "./",
				ft_strlen(verif->line));
		map_struct->north_texture[ft_strlen(map_struct->north_texture)
			- 1] = '\0';
		verif->instruct++;
	}
	else if (ft_strncmp(verif->line, "SO ", 3) == 0)
	{		
		if (!ft_find_my_str(verif->line, ft_strlen(verif->line)))
			ft_error("Bad texture name");
		map_struct->south_texture = ft_strnstr(verif->line, "./",
				ft_strlen(verif->line));
		map_struct->south_texture[ft_strlen(map_struct->south_texture)
			- 1] = '\0';
		verif->instruct++;
	}
	else if (ft_strncmp(verif->line, "WE ", 3) == 0)
	{
		if (!ft_find_my_str(verif->line, ft_strlen(verif->line)))
			ft_error("Bad texture name");
		map_struct->west_texture = ft_strnstr(verif->line, "./",
				ft_strlen(verif->line));
		map_struct->west_texture[ft_strlen(map_struct->west_texture)
			- 1] = '\0';
		verif->instruct++;
	}
}

int	ft_put_file_table(int fd, t_map *map_struct)
{
	t_verif	verif;

	verif.indic = 0;
	verif.instruct = 0;
	verif.line_pos = 0;
	verif.map_pos = 0;
	map_struct->floor_color = 0;
	map_struct->Ceiling_color = 0;
	while (verif.instruct != 6)
	{
		verif.line = get_next_line(fd);
		verif.line_pos++;
		if (verif.line == NULL)
			break ;
		ft_put_file_table2(&verif, map_struct);
		ft_put_file_table3(&verif, map_struct);
		ft_put_file_table4(&verif, map_struct);
	}
	ft_put_file_table5(&verif, map_struct, fd);
	return (verif.line_pos);
}
