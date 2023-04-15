NAME = cub3D

SRC =	main.c \
		verif_map.c \
		error.c \
		verif_shape.c \
		parsing_map.c \
		utils.c \
		check_file.c \
		display.c \
		map_modifier.c \
		path_finding1.c \
		path_finding2.c \
		path_finding3.c \
		path_finding4.c \
		utils_path_finding.c \
		raycast.c

OBJ = ${SRC:.c=.o}

CFLAGS = -arch arm64 -finline-functions -fvectorize -fslp-vectorize -ffast-math -falign-functions -funroll-loops -fstrict-aliasing -fomit-frame-pointer -flto -Ofast -O1 -O2 -Os -O3 #-g #-fsanitize=address -g

LIB  = ar rcs $(NAME) ./includes/lib/mlx/libmlx.a ./includes/lib/libft.a

REMOVE = rm -f

DEPENDS = make -C includes/lib/libft

MLX = make -C includes/lib/mlx

COMPILE = gcc $(CFLAGS) -o $(NAME) -Iincludes/lib -Iincludes/lib/mlx -Lincludes/lib/mlx -Lincludes/lib/Libft -lft -lmlx -framework OpenGL -framework Appkit -D BUFFER_SIZE=1

all: $(NAME)

libft : 
	$(DEPENDS)
	$(MLX)

$(NAME): libft $(OBJ)
	@$(COMPILE) $(OBJ)

clean:
	$(REMOVE) $(OBJ) 
	make -C includes/lib/Libft clean
	make -C includes/lib/mlx clean

fclean:	clean
	$(REMOVE) $(NAME)
	make -C includes/lib/Libft fclean

re: fclean all

.PHONY: all clean fclean re