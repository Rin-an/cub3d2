NAME = Cub3d
HEADERS = cub3d.h get_next_line/get_next_line.h
SRCS =  main.c utils.c utils2.c ft_split.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c 

OBJS := $(SRCS:.c=.o)

RM = rm -rf
FLAGS = -Werror -Wextra -Wall -Wno-unused

$(NAME): $(OBJS) $(HEADERS)
	gcc $(OBJS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

#$(NAME_B): $(B_OBJS) $(HEADER_B)
#	gcc $(B_OBJS) -lmlx -framework OpenGL -framework AppKit -o $(NAME_B)

%.o : %.c
	gcc $(FLAGS) -Imlx -c $< -o $@


all : $(NAME) #$(NAME_B)

#bonus: $(NAME_B)

clean :
	$(RM) $(OBJS) #$(B_OBJS)

fclean: clean
	$(RM) $(NAME) #$(NAME_B)

re: fclean clean all

.PHONY: all fclean clean re #bonus
