/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlinbourgeois <merlinbourgeois@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:00:16 by merlinbourg       #+#    #+#             */
/*   Updated: 2023/04/11 12:22:03 by merlinbourg      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_list(t_map_corr *chain)
{
	t_map_corr	*e;
	t_map_corr	*last;

	if (!chain)
		return ;
	while (chain->next != NULL)
	{
		e = chain;
		last = get_last(chain);
		while (e->next != last)
			e = e->next;
		free(e->next);
		e->next = NULL;
	}
}

t_map_corr	*ft_path_red3(t_map_verif *map, t_map_corr *chain)
{
	t_map_corr	*e;
	t_map_corr	*co;

	map->lower_cost = 2147483647;
	co = malloc(sizeof(t_map_corr));
	if (!co)
		return (NULL);
	co->next = NULL;
	e = get_last(chain);
	map->x = e->x;
	map->y = e->y;
	return (co);
}

t_map_corr *ft_path_finding_map_update(t_map_verif *map, t_map_corr *chain)
{
	t_map_corr	*co;

	while (map->map_compl[map->y][map->x] != 'O')
	{
		co = ft_path_red3(map, chain);
		if (ft_path_finding_map_search_neighbour(map) == 0)
		{
			return(NULL);
		}
		ft_path_red(map, chain, co);
		ft_path_red2(map, chain, co);
		if (map->lower_cost == 0)
			break ;
		else if (map->lower_cost == 2147483647)
		{
			chain = ft_path_finding_map_suppup(map, chain);
			//free(co);
		}
		else
			chain = lstadd_back(chain, co);
		//system("clear");
		// for (int k = 0; k != map->map_y; k++)
		// {
		// 	for (int l = 0; l < map->map_x; l++)
		// 	{
		// 		if (k == map->y && l == map->x)
		// 		{
		// 			printf("\e[31m%c\e[0m", map->map_compl[k][l]);
		// 		}
		// 		else
		// 			printf("%c", map->map_compl[k][l]);
		// 	}
		// 	printf("\n");
		// }
		// printf("\n");
		//usleep(300000);
	}
	//printList(chain);
	free(co);
	return (chain);
	//ft_free_list(chain);
}

t_path_return *ft_path_finding2(t_map_verif *map, char **map_path, t_map_corr co)
{
	int	i;
	t_map_corr *chain;

	i = 0;
	map->map_compl = copyStrings(map_path, map->map_y);
	ft_path_finding_map_locate(map, 'O');
	map->out_x = map->x;
	map->out_y = map->y;
	map->x = 0;
	map->y = 0;
	ft_path_finding_map_manathan(map);
	ft_path_finding_map_put_tab(map);
	ft_path_finding_map_locate(map, 'P');
	co.x = map->x;
	co.y = map->y;
	chain = ft_path_finding_map_update(map, &co);
	//while (i != map->map_y && map->map_compl[i])
	//	free(map->map_compl[i++]);
	//free(map->map_compl);
	t_path_return *coord;
	coord = list_to_arrays(chain);
	return (coord); 
}

t_path_return *ft_path_finding(t_map_verif *map, char **map_path)
{
	t_map_corr	co;
	t_map_corr *chain;
	t_path_return *coord;

	co.next = NULL;
	coord = ft_path_finding2(map, map_path, co);
	return (coord);
}
