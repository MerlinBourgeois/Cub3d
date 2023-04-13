#include "cub3d.h"



t_path_return *remove_useless_nodes(int *x, int *y, int num_nodes, char **map, int **distances)
{
    int i, j;
	t_path_return *new_moves;

	new_moves = malloc(1 * sizeof(t_path_return));
	new_moves->x = malloc(num_nodes * sizeof(int));
	new_moves->y = malloc(num_nodes * sizeof(int));
    for (i = 0; i < num_nodes-2; i++) 
	{
        if (distances[x[i+1]][y[i+1]] == distances[x[i]][y[i]] + 1)
		{
            // check if there is a straight line between node i and node i+2
            if ((x[i+2] == x[i] && y[i+2] == y[i+1]) || (x[i+2] == x[i+1] && y[i+2] == y[i]))
			{
                // if yes, remove node i+1
                for (j = i+1; j < num_nodes-1; j++)
				{
                    x[j] = x[j+1];
                    y[j] = y[j+1];
                }
                num_nodes--;
                i--;
            }
        }
    }
    // print the new path
    printf("New path: ");
    for (i = 0; i < num_nodes; i++) {
        printf("(%d,%d) ", x[i], y[i]);
    }
    printf("\n");
	new_moves->x = x;
	new_moves->y = y;
	new_moves->moves = num_nodes;
	return(new_moves);
}


t_path_return *simplify_path(char **map, int *x, int *y, int path_length)
{
    int i, j, k;
    int new_path_length = path_length;
	t_path_return *new_moves;

	new_moves = malloc(1 * sizeof(t_path_return));
	new_moves->x = malloc(path_length * sizeof(int));
	new_moves->y = malloc(path_length * sizeof(int));

    // Boucle pour simplifier le chemin
    for (i = 0; i < path_length - 2; i++)
	{
        // Vérifie si le chemin se croise
        if ((x[i] == x[i + 1]) && (y[i] == y[i + 1]))
		{
            // Vérifie si le chemin peut être simplifié
            if (map[x[i]][y[i + 1]] == '1' && map[x[i + 1]][y[i + 2]] == '1')
			{
                // Supprime le point intermédiaire
                for (j = i + 1; j < new_path_length - 1; j++)
				{
                    x[j] = x[j + 1];
                    y[j] = y[j + 1];
                }
                new_path_length--;
                i--;
            }
        }
    }

    // Met à jour la longueur du chemin simplifié
    path_length = new_path_length;

    // Affiche le chemin simplifié
    printf("Chemin simplifié : \n");
    for (k = 0; k < path_length; k++) {
        printf("(%d,%d) ", x[k], y[k]);
    }
	new_moves->x = x;
	new_moves->y = y;
	new_moves->moves = path_length;
	return(new_moves);
}

t_path_return *get_path_finding_input(char **map_map, int rows, int cols)
{
	t_map_verif *map;
	t_path_return *coord;
	char **map_path;
	int i;
	int j;

	i = 0;
	map_path = copyStrings(map_map, cols);
	map =  malloc(1 * sizeof(t_map_verif));
	while (i != cols)
	{
		j = 0;
		while (j != rows)
		{
			if (map_path[i][j] == 'W' || map_path[i][j] == 'E' || map_path[i][j] == 'S' || map_path[i][j] == 'N')
				map_path[i][j] = 'P';
			j++;
		}
		i++;
	}
	map->map_x = rows;
	map->map_y = cols;
	map->map_mapleng = cols;
	map->lower_cost = 0;
	map->x = 0;
	map->y = 0;
	map->dist = 0;
	coord = ft_path_finding(map, map_path);
	//coord = remove_useless_nodes(coord->y, coord->x, coord->moves, map_path, map->map_dist);
	i = 0;
	while (i != map->map_mapleng && map->map_dist[i])
		free(map->map_dist[i++]);
	free(map->map_dist);
	free(map);
	i = 0;
	while (i != cols)
	{
		free(map_path[i]);
		i++;
	}
	free(map_path);
	return (coord);
}
