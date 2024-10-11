DEL			=	rm -f
CC			=	cc
CCFLAGS		=	-Wall -Wextra -Werror  -g3 #-fsanitize=address
#MLX			=	-framework OpenGL -framework AppKit
 MLX			=	-lXext -lX11 -lm -lbsd 



NAME		=	cub3d


SRC_DIR		=	src/
OBJ_DIR		=	objs/

SRC_FILES	=	input/player_movement.c \
				input/player_rotation.c \
				render/frame_renderer.c \
				render/sprite_handler.c \
				render/texture_manager.c \
				map/map_parser.c \
				map/map_validator.c \
				error/color_resolution_validator.c \
				error/map_integrity_checker.c \
				error/map_boundary_validator.c \
				error/texture_file_validator.c \
				error/error_handler.c \
				core/cub3d_core.c \
				core/sprite_finder.c \
				core/key_press_handler.c \
				core/direction_setter.c \
				core/texel_handler.c \
				utils/err_utils.c \
				utils/utils.c \
				main.c

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

LIBFT		=	src/libft
MINILIBX	= 	mlx

LIBS		= $(MINILIBX)/libmlx.a $(MLX) $(LIBFT)/libft.a 


all:	minilibx libft $(NAME)

 
$(NAME):$(OBJ)
		$(CC)  $(OBJ) $(LIBS) -o $(NAME)
		@echo "CUB3D HAS BEEN COMPILED!$(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@echo "Compiling: $<$(NC)"
	@$(CC) $(CCFLAGS) -c $< -o $@ 
	@echo "Compiled!$(NC)"
	
libft:
	@echo "COMPILING LIBFT...$(NC)"
	@$(MAKE) -C ./$(LIBFT)
	@echo "LIBFT HAS BEEN COMPILED$(NC)"

minilibx:
	@echo "COMPILING MINILIBX...$(NC)"
	@$(MAKE) -C ./$(MINILIBX)
	@echo "MINILIBX HAS BEEN COMPILED$(NC)"

fclean_mlx:
	@make fclean -C ./$(MINILIBX)
	@echo "MINILIBX FULL CLEANED!$(NC)"



fclean_libft:
	@make fclean -C ./$(LIBFT)
	@echo "LIBFT FULL CLEANED!$(NC)"


clean:
	@$(RM) -rf $(OBJ_DIR)
	@echo "OBJS AND DIRECTORY CLEANED!$(NC)"


fclean: clean  fclean_libft
	@$(RM) $(NAME)
	@echo "EXECUTABLE CLEANED!$(NC)"


re: fclean all