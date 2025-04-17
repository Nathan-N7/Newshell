CC = cc

CFLAGS =  -g -Wall -Werror -Wextra 

SRCS = src/main.c \
src/parser/parser.c \
src/parser/parser_utils.c \
src/misc/utils.c \
src/parser/token_utils.c \
src/misc/env.c

NAME = minishell

LIB = includes/libft/libft.a

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make bonus -C includes/libft
	$(CC) $(OBJS) -lreadline -o  $(NAME) $(LIB)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C includes/libft
	rm -f $(OBJS)

fclean:
	make fclean -C includes/libft
	rm -f $(NAME) $(OBJS)

re: fclean $(NAME)

