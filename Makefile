DEL			=	rm -f
CC			=	cc
CCFLAGS		=	-Wall -Wextra -Werror -g3 # -fsanitize=address
#MLX			=	-framework OpenGL -framework AppKit
 MLX			=	-lXext -lX11 -lm -lbsd 



NAME		=	cub3d


SRC_FILES	=change_move \
			change_rot \
			cub \
			error_colres \
			error_imap \
			error_map \
			error_txts \
			errors \
			findspr \
			keypress \
			map_body \
			read_map \
			renderframe \
			setdir \
			sprites \
			texel \
			textures \
			error_utils \
			utils \
			main
	

SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

LIBFT		=	srcs/libft
MINILIBX	= 	mlx


LIBS		= $(MINILIBX)/libmlx.a $(MLX) $(LIBFT)/libft.a 


SRC_DIR = srcs/
OBJ_DIR = objs/


all:	minilibx libft $(NAME)

 
$(NAME):$(OBJ)
		$(CC)  $(OBJ) $(LIBS) -o $(NAME)
		@echo "CUB3D HAS BEEN COMPILED!$(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling: $<$(NC)"
	@$(CC) $(CCFLAGS) -o $@ -c $< 
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
	@echo "$(RED)LIBFT FULL CLEANED!$(NC)"


clean:
	@$(RM) -rf $(OBJ_DIR)
	@echo "$(RED)OBJS AND DIRECTORY CLEANED!$(NC)"


fclean: clean  fclean_libft
	@$(RM) $(NAME)
	@echo "$(RED)EXECUTABLE CLEANED!$(NC)"

run: re
	./cub3d maps/map1.cub

val: re
	valgrind -s ./cub3d maps/map1.cub


re: fclean all