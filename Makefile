#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2017/01/23 15:37:07 by psebasti          #+#    #+#             *#
#*   Updated: 2017/01/23 16:29:09 by psebasti         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME = get_next_line

SRC = get_next_line.c \
	  main.c

OBJ		=	$(SRC:.c=.o)

CMP		=	gcc

FLAGS	=	-Wall -Wextra -Werror

LIB = -L libft/ -lft

all : lib $(NAME)

$(NAME) :
	$(CMP) $(FLAGS) -o $(NAME) $(SRC) $(LIB)

lib :
	make re -C libft

clean :
	rm -rf $(OBJ)
	make -C libft clean

fclean : clean
	rm -rf $(NAME)
	make -C libft fclean

re : fclean all
