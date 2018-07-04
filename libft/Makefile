# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdurst <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 12:23:27 by rdurst            #+#    #+#              #
#    Updated: 2018/07/03 21:41:44 by rdurst           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CFILES = $(addsuffix .c, $(SRCS))
OFILES = $(addsuffix .o, $(SRCS))
INC = libft.h
SRCS =\
	ft_atoi\
	ft_bzero\
	ft_isalnum\
	ft_isalpha\
	ft_isascii\
	ft_isdigit\
	ft_isprint\
	ft_itoa\
	ft_memalloc\
	ft_memccpy\
	ft_memchr\
	ft_memcmp\
	ft_memcpy\
	ft_memdel\
	ft_memmove\
	ft_memset\
	ft_putchar\
	ft_putchar_fd\
	ft_putendl\
	ft_putendl_fd\
	ft_putnbr\
	ft_putnbr_fd\
	ft_putstr\
	ft_putstr_fd\
	ft_strcat\
	ft_strchr\
	ft_strclr\
	ft_strcmp\
	ft_strcpy\
	ft_strucpy\
	ft_strdel\
	ft_strdup\
	ft_strequ\
	ft_striter\
	ft_striteri\
	ft_strjoin\
	ft_strlcat\
	ft_strlen\
	ft_strmap\
	ft_strmapi\
	ft_strncat\
	ft_strncmp\
	ft_strncpy\
	ft_strnequ\
	ft_strnew\
	ft_strnstr\
	ft_strrchr\
	ft_strsplit\
	ft_strstr\
	ft_strtrim\
	ft_tolower\
	ft_strsub\
	ft_toupper\
	ft_lstnew\
	ft_lstdelone\
	ft_lstdel\
	ft_lstiter\
	ft_lstmap\
	ft_lstadd\
	ft_intendl\
	ft_countwords\
	ft_wordlen\
	ft_trimsize\
	ft_intsize\
	ft_isblanked\
	ft_putcolor\
	ft_nbrlen

RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
RESET = \033[0m

.PHONY: re clean fclean all

all: $(NAME)

$(NAME): $(CFILES) libft.h Makefile
	@$(CC) $(CFLAGS) -I $(INC) -c $(CFILES)
	@ar rc $(NAME) $(OFILES)
	@ranlib $(NAME)
	@echo "$(RED)\t\t\t(LIBFT)\t$(GREEN)libft has been built.$(RESET)"

clean:
	@rm -f $(OFILES)
	@echo "$(RED)\t\t\t(LIBFT)\t$(GREEN)object files removed.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)\t\t\t(LIBFT)\t$(RED)libft.a removed.$(RESET)"

re:	fclean all
