NAME = minishell

CC = cc

FLAGS = -g -Wall -Werror -Wextra -Ilibs

SRCS = \
	main/minishell.c \
	main/sig_main.c \
	parser/parsing.c \
	parser/tokenizar.c \
	parser/syntax_analizer.c \
	utils/utils_toke.c \
	utils/utils_ps1.c \
	utils/utils_ps2.c \
	utils/expand.c \
	pipe/pipe.c \
	pipe/aux_pipe.c \
	pipe/heredoc_pipe.c \
	pipe/pid_utils.c \
	builtins/ft_env.c \
	builtins/ft_pwd.c \
	builtins/ft_echo.c \
	builtins/ft_cd.c \
	builtins/ft_export.c \
	builtins/ft_unset.c \
	builtins/ft_exit.c \
	redirects/pathname_utils.c \
	redirects/redirect.c \
	redirects/redout.c \
	redirects/redin.c \
	redirects/append.c \
	redirects/heredoc.c \
	executor/executor.c 

OBJS = $(SRCS:.c=.o)

LIBFT = my_lib/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) -lreadline -o $(NAME) $(LIBFT)

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	@make -C my_lib

clean:
	@rm -rf $(OBJS)
	@make -C my_lib clean

fclean: clean
	@rm -f $(NAME)
	@make -C my_lib fclean

re: fclean all

