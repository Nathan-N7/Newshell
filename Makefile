CC = cc

CFLAGS =  -g -Wall -Werror -Wextra 

SRCS = src/main.c \
src/parser/parser.c \
src/parser/parser_utils.c \
src/misc/utils.c \
src/parser/token_utils.c \
src/misc/env.c \
src/parser/syntax_utils.c \
src/parser/expansion_utils.c \
src/redirect/fd_utils.c \
src/redirect/pathname_utils.c \
src/redirect/redirect_out.c \
src/redirect/redirect.c \
src/redirect/append.c \
src/redirect/redirect_in.c \
src/redirect/heredoc.c \
src/executor/executor.c

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

