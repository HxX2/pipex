# MakeFile

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_fprintf.c ft_fprintf_utils.c
NAME = libftprintf.a
OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	ar crs $(NAME) $(OBJS)

clean : 
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re 