CC = cc

CFLAGS =  -g -Wall -Werror -Wextra 

SRCS = src/main.c \
src/parser.c \
src/parser_utils.c \
src/utils.c \
src/token_utils.c

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

