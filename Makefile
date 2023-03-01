NAME = Cub3d
HEADERS = cub3d.h get_next_line/get_next_line.h
SRCS =  main.c utils.c 
EXECUTION = dda.c hooks.c player_movements.c draw.c init_settings.c render_map.c exit.c

OBJS := $(SRCS:.c=.o) $(EXECUTION:.c=.o)
RM = rm -rf
FLAGS = -Werror -Wextra -Wall

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
