# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/16 18:31:56 by msoulaim          #+#    #+#              #
#    Updated: 2021/01/17 14:21:59 by msoulaim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = builtins.c env.c exe.c free.c input_handler.c minishell.c set_unset.c util_2.c utils.c

OBJ = $(SRCS:.c=.o)

CC = gcc -Wall -Wextra -Werror

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) minishell.h
	@make -C libft/
	$(CC) -o $(NAME) $(OBJ) $(LIBFT)

clean:
	@make clean -C libft/
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C libft/
	@rm -f $(NAME)

re: fclean all

norme:
	norminette $(SRCS)
	norminette minishell.h