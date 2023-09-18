CC = cc
INCLUDES = cub3D.h
CFLAGS =  -Wall -Wextra -Werror -fsanitize=address -g
GLFW = $(shell brew --prefix glfw)
FRAMEWORKS = /Users/aouchaad/MLX42/build/libmlx42.a -Iinclude -lglfw -L $(GLFW)/lib/ -framework Cocoa -framework OpenGL -framework IOKit
NAME = cub3D

LIBFT_SRCS = $(addprefix ./libft/, ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c get_next_line.c)
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)

PARSING_SRCS= $(addprefix ./parsing/, map_checker.c read_map.c parser_utils.c scene_checker.c scene_elements.c parser_utils2.c)
PARSING_OBJS = $(PARSING_SRCS:.c=.o)

MANDATORY_SRCS	=	$(addprefix ./mandatory/,  main.c utils.c utils2.c utils3.c horizontal_intersept.c vertical_intersept.c ray_casting.c draw_functions.c key_handling.c)
MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)

BONUS_SRCS	=	$(addprefix ./bonus/,  main_bonus.c utils_bonus.c utils2_bonus.c utils3_bonus.c horizontal_intersept_bonus.c vertical_intersept_bonus.c ray_casting_bonus.c draw_functions_bonus.c key_handling_bonus.c moving_possibility_bonus.c)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

MANDATORY = $(MANDATORY_OBJS) $(PARSING_OBJS) $(LIBFT_OBJS)
BONUS = $(BONUS_OBJS) $(PARSING_OBJS) $(LIBFT_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I ./includes -c $^

all: $(NAME)

$(NAME): $(MANDATORY)
	make -C libft
	$(CC) $(CFLAGS) $(MANDATORY) -L./libft -lft  ${FRAMEWORKS} -o $@

bonus: $(BONUS)
	make -C libft
	$(CC) $(CFLAGS) $(BONUS) -L./libft -lft  ${FRAMEWORKS} -o $@

clean:
	make -C libft clean
	rm -f $(MANDATORY)
	rm -f $(BONUS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

run: all
	./${NAME} maps/subject_map.cub

.PHONY: clean fclean all re
