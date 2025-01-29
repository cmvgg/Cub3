# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 15:45:40 by cvarela-          #+#    #+#              #
#    Updated: 2025/01/29 18:12:53 by cvarela-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEL			=	rm -f
CC			=	gcc
CCFLAGS		=	-Wall -Wextra -Werror -Wuninitialized -g3 #-fsanitize=address,leak
BONUSFLAGS	=	-D BONUS=1
#MLX			=	-framework OpenGL -framework AppKit
 MLX			=	-lXext -lX11 -lm -lbsd 



NAME		=	cub3D


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
			sprites_2 \
			texel \
			textures \
			error_utils \
			utils \
			main \
			\
			minimap_bonus \
			mouse_bonus

	

SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
OBJ_BONUS	=	$(addprefix $(OBJ_DIR_BONUS), $(addsuffix .o, $(SRC_FILES)))

LIBFT		=	srcs/libft
MINILIBX	= 	mlx


LIBS		= $(MINILIBX)/libmlx.a $(MLX) $(LIBFT)/libft.a 


SRC_DIR 		= srcs/
OBJ_DIR 		= objs/
OBJ_DIR_BONUS	= objs_bonus/


all:	minilibx libft $(NAME)
bonus:	minilibx libft $(NAME)_bonus

 
$(NAME):$(OBJ)
		$(CC) $(CCFLAGS)  $(OBJ) $(LIBS) -o $(NAME)
		@echo "CUB3D HAS BEEN COMPILED!$(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling: $<$(NC)"
	@$(CC) $(CCFLAGS) -o $@ -c $< 
	@echo "Compiled!$(NC)"
	
$(NAME)_bonus:$(OBJ_BONUS)
		$(CC) $(CCFLAGS) $(BONUSFLAGS) $(OBJ_BONUS) $(LIBS) -o $(NAME)_bonus
		@echo "CUB3D BONUS HAS BEEN COMPILED!$(NC)"

$(OBJ_DIR_BONUS)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR_BONUS)
	@echo "Compiling: $<$(NC)"
	@$(CC) $(CCFLAGS) $(BONUSFLAGS) -o $@ -c $< 
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
	@make clean -C ./$(MINILIBX)
	@echo "MINILIBX FULL CLEANED!$(NC)"



fclean_libft:
	@make fclean -C ./$(LIBFT)
	@echo "$(RED)LIBFT FULL CLEANED!$(NC)"


clean:
	@$(RM) -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)
	@echo "$(RED)OBJS AND DIRECTORY CLEANED!$(NC)"


fclean: clean  fclean_libft fclean_mlx
	@$(RM) $(NAME) $(NAME)_bonus
	@echo "$(RED)EXECUTABLE CLEANED!$(NC)"

run: re
	./cub3D maps/map5.cub

val: re
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.txt ./cub3D maps/map5.cub #

norm: 
	norminette srcs includes

re: fclean all