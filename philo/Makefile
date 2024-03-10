# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmahdi <bmahdi@student.42vienna.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/09 17:37:19 by bmahdi            #+#    #+#              #
#    Updated: 2024/03/10 02:32:57 by bmahdi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = clang
CFLAGS = -Wall -Wextra -Werror clang -fsanitize=address -g
SRC = philo.c data_init.c utils.c utils_libft.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all