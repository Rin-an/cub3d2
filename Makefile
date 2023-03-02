# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/15 17:31:50 by fabou-za          #+#    #+#              #
#    Updated: 2023/03/01 15:34:19 by ssadiki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
HEADERS = cub3d.h get_next_line/get_next_line.h
SRCS =  main.c utils.c utils2.c ft_split.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c ft_strtrim.c \
map.c parsing.c parsing_utils.c color.c check_identifiers.c 
EXECUTION = dda.c hooks.c player_movements.c draw.c init_settings.c render_map.c exit.c img_pix_put.c

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
