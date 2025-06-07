# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/01 13:33:33 by natrodri          #+#    #+#              #
#    Updated: 2025/05/27 16:05:02 by lbarreto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -g -Wall -Werror -Wextra

FUNCTIONS = ft_isprint.c     ft_putendl_fd.c  ft_strlcat.c  ft_substr.c \
ft_atoi.c     ft_itoa.c        ft_putnbr_fd.c   ft_strlcpy.c  ft_tolower.c \
ft_bzero.c    ft_memchr.c      ft_putstr_fd.c   ft_strlen.c   ft_toupper.c \
ft_calloc.c   ft_memcmp.c      ft_split.c       ft_strmapi.c \
ft_isalnum.c  ft_memcpy.c      ft_strchr.c      ft_strncmp.c \
ft_isalpha.c  ft_memmove.c     ft_strdup.c      ft_strnstr.c \
ft_isascii.c  ft_memset.c      ft_striteri.c    ft_strrchr.c \
ft_isdigit.c  ft_putchar_fd.c  ft_strjoin.c     ft_strtrim.c ft_strndup.c \
ft_strcmp.c	ft_printf_fd.c	ft_printf.c	ft_putchar.c	ft_putnbr.c \
ft_putnbr_base.c	ft_putpointer.c	ft_putstr.c

BONUS_FCT = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJECTS=$(FUNCTIONS:.c=.o)

BONUS_OBJ=$(BONUS_FCT:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@ar rcs $(NAME) $(OBJECTS)

.c.o:
	cc $(FLAGS) -c $< -o $@

BONUS_OBJ: $(BONUS_FCT)
	@cc -Wall -Wextra -Werror -c $(BONUS_FCT) -o $(BONUS_OBJ)

bonus: $(BONUS_OBJ) $(NAME)

clean:
	@rm -f $(OBJECTS) $(BONUS_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
