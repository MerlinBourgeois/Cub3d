#ifndef CUB3D_H
#define CUB3D_H

/*
*	Macros de gestion d'erreur
*/

# define CHAR_ERROR "Unrecognized characters"
# define MAP_LAYOUT_ERROR "Bad map layout"
# define ARGUMENT_ERROR "Invalid argument"
# define FILE_DESRIPTOR_ERROR "Bad file descriptor"
# define BAD_PLAYER_ERROR "Not enough or too many players present on the map"
# define BAD_FILE "Bad file arrangement"

/*
*	Macros de gestion des visuels
*/

# define SCREEN_HEIGHT 700
# define SCREEN_WIDTH 1200
# define TITLE_SCREEN "Cub3D"
# define MAX_FPS 60
# define MINIMAP_X 170
# define MINIMAP_Y 170

#define FOV M_PI/3.0
#define NUM_RAYS SCREEN_WIDTH

/*
*	Macros de gestion mathematique
*/

# define PI 3.141592
# define CASTED_RAYS 1400
# define STEP_ANGLE FOV / CASTED_RAYS
# define SCALE (SCREEN_WIDTH / 2) / CASTED_RAYS

/*
*	Includes
*/

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include "includes/lib/mlx/mlx.h"
# include "includes/lib/Libft/libft.h"
# include "includes/lib/Libft/get_next_line.h"

typedef enum e_directions
{
	SOUTH = 1,
	NORTH = 13,
	EAST = 2,
	WEST = 0,
	ESC = 53,
}	t_directions;

/*
*	structure de gestion du raycasting
*/

typedef struct s_ray
{
    float x, y; // Position de départ du rayon
    float dx, dy; // Direction du rayon (vecteur unitaire)
    float maxDistance; // Distance maximale que peut parcourir le rayon
} t_ray;

/*
*	structure de gestion du joueur
*/

typedef struct s_player
{
	float delta_x;
	float delta_y;
	float player_angle;
	float x;
	float y;
}	t_player;

/*
*	structure de gestion de la mlx
*/

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	int		color;
}	t_mlx;

/*
*	structure de gestion de l'image génerale imprimée
*/

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

/*
*	Structure de gestion des infos contenue dans le fichier
*/

typedef struct s_map
{
	int		def_x;
	int		def_y;
	char	def_angle;
	char	*north_texture;
	char	*south_texture;
	char	*east_texture;
	char	*west_texture;
	int		floor_color;
	int		Ceiling_color;
	int		map_lenght;
	int		map_len;
	int		map_max;
	char	*map_line;
	char	**map;
}	t_map;

/*
*	Structure de verification de la map
*/

typedef struct s_verif
{
	char	**map;
	char	*line;
	char	**tmp;
	int		instruct;
	int		line_pos;
	int		map_pos;
	int		indic;
	int	i;
	int	j;
}	t_verif;

/*
*	structure de gestion des autres structures
*/

typedef struct	s_s
{
	t_data	*img;
	t_map	*map;
	t_mlx	*p;
	t_player *player;
}	t_s;


/*
*	structure de gestion du path_finding
*/

typedef struct s_map_verif
{
	int		error;
	char	*map_path;
	int		map_x;
	int		map_y;
	int		x;
	int		y;
	int		out_x;
	int		out_y;
	int		dist;
	int		map_mapleng;
	int		lower_cost;
	int		**map_dist;
	char	**map_compl;
}	t_map_verif;

/*
*	liste chainée du path_finding
*/

typedef struct s_map_corr
{
	int					x;
	int					y;
	struct s_map_corr	*next;
}	t_map_corr;

/*
*	structure de return du path_finding
*/

typedef struct s_path_return
{
	int moves;
	int *x;
	int *y;
}	 t_path_return;

/*
*	structure de gestion des vecteurs du raycasting
*/

typedef struct {
    float x;
    float y;
} vec2;


/*
*	structure de gestion de la camera dans le raycating
*/

typedef struct {
    vec2 pos;
    vec2 dir;
} camera_t;

/*
*	structure de gestion génerale du raycating
*/

typedef struct {
    float distance;
    vec2 wallHit;
    char wallType;
    char wallFace;
} ray_t;


/*
*	Parsing_map.c
*/

int	ft_put_file_table(int fd, char **argv, t_map *map_struct);

/*
*	Verif_shape.c
*/

int	ft_verif_map_shape(t_map *map);

/*
*	Verif_map.c
*/

void ft_verif_char_map(t_map *map);
void ft_print_map(t_map *map);

/*
*	Error.c
*/

void	ft_error(char *str);

/*
*	Utils.c
*/

void	free_tab(char **tmp);
void	*ft_realloc(void *p, size_t size);

/*
*	Check_file.c
*/

char	**ft_allocate_table(int fd, t_map *map_struct, int line_pos, char **argv);
t_map	check_map(int fd, char **argv);

/*
*	Display.c
*/

void	display_window(t_map *map);

/*
*	Map_modifier.c
*/

void	space_to_one(t_map *map);

/*
*	Fonctions destinées au bon fonctionement du path_finding
*/

char **copyStrings(char** src, int numStrings);
t_path_return *list_to_arrays(t_map_corr* head);
t_path_return *get_path_finding_input(char **map_path, int rows, int cols);

void		ft_path_red2(t_map_verif *map, t_map_corr *chain, t_map_corr *co);
void		ft_path_red(t_map_verif *map, t_map_corr *chain, t_map_corr *co);
int			ft_path_finding_map_search_neighbour(t_map_verif *map);
t_map_corr	*ft_path_finding_map_suppup(t_map_verif *map, t_map_corr *chain);
int			ft_path_finding_alredy(int y, int x, t_map_corr *chain);
void		ft_path_finding_map_locate(t_map_verif *map, char c);
void		ft_path_finding_map_put_tab(t_map_verif *map);
void		ft_path_finding_map_manathan(t_map_verif *map);
t_map_corr	*lstadd_back(t_map_corr *chain, t_map_corr *co);
t_map_corr	*get_last(t_map_corr *chain);
t_path_return *ft_path_finding(t_map_verif *map, char **map_path);
size_t		ft_strlen_back(const char *s);
void		printList(t_map_corr* head);

/*
*	display.c
*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

/*
*	raycast.c
*/

void	cast_rays(t_s *s);

#endif