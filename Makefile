# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdurst <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/14 16:16:42 by rdurst            #+#    #+#              #
#    Updated: 2018/07/05 02:19:41 by rdurst           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls
CC=gcc
INCLUDES= -I ./includes -I ./libft
LIBFT= libft/libft.a
SRCS= ./srcs/main.c\
	./srcs/options.c\
	./srcs/padding.c\
	./srcs/dir.c\
	./srcs/error.c\
	./srcs/utils.c\
	./srcs/args.c\
	./srcs/sort.c\
	./srcs/stats.c\
	./srcs/print.c\
	./srcs/count.c\
	./srcs/free.c\
	./srcs/majorminor.c\

OPTIONS= -Wall -Wextra -Werror
DEBUGFLAG= -g3
RM= rm -rf

RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
RESET = \033[0m

$(NAME):
	@make -C libft
	@$(CC) $(SRCS) $(INCLUDES) $(LIBFT) -o $(NAME) $(OPTIONS)
	@echo "$(BLUE)\t\t\t\tft_ls has been built.$(RESET)"

clean:
	@make -C libft fclean

fclean: clean
	@$(RM) $(NAME)
	@echo "$(BLUE)\t\t\t\tft_ls has been removed.$(RESET)"

re: fclean all

all: $(NAME)
