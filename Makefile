SRC = pipex.c src/exe.c src/forbidden.c src/ft_split.c src/pipex_utils.c src/str_utils.c src/str_utils2.c src/fprintf/libftprintf.a
CC = gcc
NAME = pipex
FLAGS = -Wextra -Werror -Wall
HEADER = "\033[0;35m   █▀▀█ ░▀░ █▀▀█ █▀▀ █░█ \n   █░░█ ▀█▀ █░░█ █▀▀ ▄▀▄ \n   █▀▀▀ ▀▀▀ █▀▀▀ ▀▀▀ ▀░▀\033[0;0m"

all: $(NAME)

header :
	@echo
	@echo $(HEADER)
	@echo

$(NAME): header
	@echo "\033[0;35m\033[1m────── making fprintf ──────\033[0;0m"
	@printf "\033[2m"
	@$(MAKE) -C src/fprintf/
	@echo "\033[0;0m"
	@echo "\033[0;35m\033[1m────── making pipex ──────\033[0;0m"
	@printf "\033[2m"
	$(CC) $(FLAGS) -o $(NAME) $(SRC)
	@echo "\033[0;0m"

clean: header
	@echo "\033[0;35m\033[1m────── clean fprintf ──────\033[0;0m"
	@printf "\033[2m"
	@$(MAKE) clean -C src/fprintf/
	@echo "\033[0;0m"

fclean: header clean
	@echo "\033[0;35m\033[1m────── fclean pipex ──────\033[0;0m"
	@printf "\033[2m"
	rm -rf $(NAME)
	@echo "\033[0;0m"
	@echo "\033[0;35m\033[1m────── fclean fprintf ──────\033[0;0m"
	@printf "\033[2m"
	@$(MAKE) fclean -C src/fprintf/
	@echo "\033[0;0m"

re: fclean all

san:
	$(CC) $(FLAGS) -o $(NAME) $(SRC) -g -fsanitize=address

sre: fclean san

.PHONY: all clean fclean re san sre
	