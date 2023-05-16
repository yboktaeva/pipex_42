# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 14:54:55 by yuboktae          #+#    #+#              #
#    Updated: 2023/05/16 15:00:57 by yuboktae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex

INCL			=	-I../includes
SRC_DIR			=	src/
OBJ_DIR			=	obj/

SRC_FILES		=	pipex.c \
					fork.c \
					free.c \
					utils.c \
					utils2.c \
					msg_error.c \

SRC				=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ				=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -g3

all:	$(NAME)

$(NAME): $(OBJ)
	@echo "$(BGreen)******* Mandatory: Compilation complete! *******$(BEnd)"
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	@mkdir -p $(@D)
	$(CC) $(INCL) $(CFLAGS) -MMD -MP -o $@ -c $<
	
-include $(SRC_FILES:.c=.d)

clean:
	rm -rf $(OBJ_DIR)

fclean:	clean
	rm -f $(NAME)
	rm -f outfile
	@echo "$(BBlue)******* Cleanup complete! *******$(BEnd)"

re:	fclean all

.PHONY:	all clean fclean re 

BGreen=\033[1;32m
BBlue=\033[1;34m
BEnd=\033[1m
