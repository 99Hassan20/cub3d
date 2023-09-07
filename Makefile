CC = cc
CFLAGS =  #-fsanitize=address -g
GLFW = $(shell brew --prefix glfw)
FRAMEWORKS = /Users/hoigag/MLX42/libmlx42.a -Iinclude -lglfw -L $(GLFW)/lib/ -framework Cocoa -framework OpenGL -framework IOKit

LIBFT_SRCS = $(addprefix ./libft/, ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c get_next_line.c)
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)

NAME = cub3D

SRCS_PARSING= $(addprefix ./srcs/parsing/, map_checker.c read_map.c parser_utils.c scene_checker.c scene_elements.c parser_utils2.c)
SRCS_RC	=	$(addprefix ./srcs/rc/,  main.c \
			utils.c \
			utils2.c \
			utils3.c \
			horizontal_intersept.c \
			vertical_intersept.c \
			ray_casting.c \
			draw_functions.c \
			moving_possibility.c \
			key_handling.c)
OBJS = $(SRCS_PARSING:.c=.o) $(SRCS_RC:.c=.o)

.srcs/%.o: %.c
	$(CC) $(CFLAGS) -c $^

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_OBJS) cub3D.h
	make -C libft
	$(CC) $(CFLAGS)   $(OBJS) -L./libft -lft ${FRAMEWORKS} -o $@

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

run: all
	./${NAME} maps/valid_map.cub

.PHONY: clean fclean all re
