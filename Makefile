NAME = Cub3d
HEADERS = cub3d.h get_next_line/get_next_line.h
SRCS =  main.c utils.c utils2.c ft_split.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c 
EXECUTION = dda.c

OBJS := $(SRCS:.c=.o) $(EXECUTION:.c=.o)
RM = rm -rf
FLAGS = -Werror -Wextra -Wall -Wno-unused

$(NAME): $(OBJS) $(HEADERS)
	gcc $(OBJS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o : %.c $(HEADERS)
	gcc $(FLAGS) -Imlx -c $< -o $@

all : $(NAME)


clean :
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean clean all

.PHONY: all fclean clean re
