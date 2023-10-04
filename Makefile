CC = cc
INCLUDES = cub3D.h
CFLAGS =  -Wall -Wextra -Werror -I./includes -O3 -fsanitize=address -g
GLFW = $(shell brew --prefix glfw)
FRAMEWORKS = /Users/hoigag/MLX42/libmlx42.a -Iinclude -lglfw -L $(GLFW)/lib/ -framework Cocoa -framework OpenGL -framework IOKit
NAME = cub3D
NAME_BONUS = cub3D_bonus

LIBFT_SRCS = $(addprefix libft/, ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c get_next_line.c)

PARSING_MANDATORY_SRCS= $(addprefix parsing/, parser_utils3.c map_checker.c read_map.c parser_utils.c scene_checker.c scene_elements.c parser_utils2.c)

PARSING_BONUS_SRCS= $(addprefix parsing_bonus/, doors_checker_bonus.c parser_utils3_bonus.c map_checker_bonus.c read_map_bonus.c parser_utils_bonus.c scene_checker_bonus.c scene_elements_bonus.c parser_utils2_bonus.c)

MANDATORY_SRCS	=	$(addprefix mandatory/,  main.c utils.c textures_funcs.c moving_possibility.c utils2.c utils3.c horizontal_intersept.c vertical_intersept.c ray_casting.c draw_functions.c key_handling.c)

BONUS_SRCS	=	$(addprefix bonus/,  main_bonus.c utils_bonus.c utils2_bonus.c utils3_bonus.c utils4_bonus.c utils5_bonus.c textures_funcs_bonus.c horizontal_intersept_bonus.c vertical_intersept_bonus.c ray_casting_bonus.c draw_functions_bonus.c key_handling_bonus.c moving_possibility_bonus.c)

MANDATORY = $(MANDATORY_SRCS) $(PARSING_MANDATORY_SRCS) $(LIBFT_SRCS)

MANDATORY_OBJS = $(MANDATORY:.c=.o)

BONUS = $(BONUS_SRCS) $(PARSING_BONUS_SRCS) $(LIBFT_SRCS)

BONUS_OBJS = $(BONUS:.c=.o)


all: $(NAME)


$(NAME): $(MANDATORY_OBJS)
	make -C libft bonus
	$(CC) $(CFLAGS) $(MANDATORY_OBJS) -L./libft -lft  ${FRAMEWORKS} -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(BONUS_OBJS)
	make -C libft bonus
	$(CC) $(CFLAGS) $(BONUS_OBJS) -L./libft -lft  ${FRAMEWORKS} -o $@

clean:
	make -C libft clean
	rm -f $(MANDATORY_OBJS)
	rm -f $(BONUS_OBJS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all

run: all
	./${NAME} maps/subject_map.cub

runb: $(NAME_BONUS)
	./$(NAME_BONUS) maps/subject_map_bonus.cub

.PHONY: clean fclean all re
