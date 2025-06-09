NAME = minishell

CC = cc

FLAGS = -g -Wall -Werror -Wextra -Ilibs

SRCS = \
	main/minishell.c \
	parser/parsing.c \
	parser/tokenizar.c \
	parser/syntax_analizer.c \
	utils/utils_toke.c \
	utils/utils_ps1.c \
	utils/utils_ps2.c \
	utils/expand.c \
	pipe/pipe.c \
	pipe/aux_pipe.c \
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

OBJDIR = objects
OBJS = $(SRCS:.c=.o)
LIBFT = my_lib/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) | $(OBJDIR)
	$(CC) $(FLAGS) $(OBJS) -lreadline -o $(NAME) $(LIBFT)
	@mv -f $(OBJS) $(OBJDIR)/

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	@make -C my_lib

clean:
	@rm -rf $(OBJDIR)
	@make -C my_lib clean

fclean: clean
	@rm -f $(NAME)
	@make -C my_lib fclean

re: fclean all


# OBJECTS = \
# 	objects/minishell.o \
# 	objects/parsing.o \
# 	objects/tokenizar.o \
# 	objects/utils_toke.o \
# 	objects/utils_ps1.o	\
# 	objects/utils_ps2.o \
# 	objects/expand.o \
# 	objects/pipe.o \
# 	objects/aux_pipe.o \
# 	objects/ft_env.o \
# 	objects/ft_pwd.o \
# 	objects/ft_echo.o \
# 	objects/ft_cd.o \
# 	objects/ft_export.o \
# 	objects/ft_unset.o \
# 	objects/ft_exit.o \
# 	objects/pathname_utils.o \
# 	objects/redirect.o \
# 	objects/redout.o \
# 	objects/redin.o \
# 	objects/append.o \
# 	objects/heredoc.o \
# 	objects/syntax_analizer.o

# $(NAME): $(LIBFT) $(OBJECTS)
# 	@cc $(FLAGS) -o $(NAME) $(OBJECTS) -L my_lib -lft -lreadline -lhistory

# objects/minishell.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c main/minishell.c -o objects/minishell.o

# objects/parsing.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c parser/parsing.c -o objects/parsing.o

# objects/tokenizar.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c parser/tokenizar.c -o objects/tokenizar.o

# objects/utils_toke.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c utils/utils_toke.c -o objects/utils_toke.o

# objects/utils_ps1.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c utils/utils_ps1.c -o objects/utils_ps1.o

# objects/utils_ps2.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c utils/utils_ps2.c -o objects/utils_ps2.o

# objects/expand.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c utils/expand.c -o objects/expand.o

# objects/pipe.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c pipe/pipe.c -o objects/pipe.o
	
# objects/aux_pipe.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c pipe/aux_pipe.c -o objects/aux_pipe.o

# objects/ft_env.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c builtins/ft_env.c -o objects/ft_env.o

# objects/ft_pwd.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c builtins/ft_pwd.c -o objects/ft_pwd.o

# objects/ft_echo.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c builtins/ft_echo.c -o objects/ft_echo.o

# objects/ft_cd.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c builtins/ft_cd.c -o objects/ft_cd.o

# objects/ft_export.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c builtins/ft_export.c -o objects/ft_export.o

# objects/ft_unset.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c builtins/ft_unset.c -o objects/ft_unset.o

# objects/ft_exit.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c builtins/ft_exit.c -o objects/ft_exit.o

# objects/pathname_utils.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c redirects/pathname_utils.c -o objects/pathname_utils.o

# objects/redirect.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c redirects/redirect.c -o objects/redirect.o

# objects/redout.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c redirects/redout.c -o objects/redout.o

# objects/redin.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c redirects/redin.c -o objects/redin.o

# objects/append.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c redirects/append.c -o objects/append.o

# objects/heredoc.o:
# 	@mkdir -p objects
# 	@cc $(FLAGS) -c redirects/heredoc.c -o objects/heredoc.o
