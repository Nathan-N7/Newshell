CC = cc

CFLAGS = -Wall -Werror -Wextra

NAME = libft.a

SRCS = ft_isascii.c \
ft_memcpy.c \
ft_putstr_fd.c \
ft_strlcat.c \
ft_strrchr.c \
ft_atoi.c \
ft_isdigit.c \
ft_memmove.c \
ft_split.c \
ft_strlcpy.c \
ft_strtrim.c \
ft_bzero.c \
ft_isprint.c \
ft_memset.c \
ft_strchr.c	\
ft_strlen.c \
ft_substr.c \
ft_calloc.c \
ft_itoa.c \
ft_putchar_fd.c \
ft_strdup.c \
ft_strmapi.c \
ft_tolower.c \
ft_isalnum.c \
ft_memchr.c \
ft_putendl_fd.c \
ft_striteri.c \
ft_strncmp.c \
ft_toupper.c \
ft_isalpha.c \
ft_memcmp.c \
ft_putnbr_fd.c \
ft_strjoin.c \
ft_strnstr.c \
ft_putnbr_base.c	\
ft_putnbr.c  \
ft_putstr.c  \
ft_printf.c   \
ft_putpointer.c \
get_next_line_utils.c \
get_next_line.c \
ft_putchar.c \
ft_putnbr.c \
ft_putstr.c \
ft_putnbr_base.c \
ft_putpointer.c \
ft_atol.c


BONUS_SRCS = ft_lstnew_bonus.c	ft_lstadd_front_bonus.c	ft_lstsize_bonus.c \
ft_lstlast_bonus.c	ft_lstadd_back_bonus.c	ft_lstdelone_bonus.c	\
ft_lstclear_bonus.c	ft_lstiter_bonus.c	ft_lstmap_bonus.c

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean: 
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

bonus: $(NAME) $(BONUS_OBJS)
	@ar rcs $(NAME) $(BONUS_OBJS)
