SRC = pipex.c src/exe.c src/ft_split.c src/pipex_utils.c src/str_utils.c src/str_utils2.c src/fprintf/libftprintf.a 
BSRC = pipex_bonus.c src/exe_bonus.c src/ft_split.c src/pipex_utils.c src/str_utils.c src/str_utils2.c src/fprintf/libftprintf.a src/heredoc_bonus.c src/gnl/get_next_line.c
CC = gcc
NAME = pipex
BNAME = pipex_bonus
FLAGS = -Wextra -Werror -Wall
HEADER = "\033[0;35m   █▀▀█ ░▀░ █▀▀█ █▀▀ █░█ \n   █░░█ ▀█▀ █░░█ █▀▀ ▄▀▄ \n   █▀▀▀ ▀▀▀ █▀▀▀ ▀▀▀ ▀░▀\033[0;0m"
FOOTER = "\033[0;35m➔\033[0;0m type \033[0;34m./pipex\033[0;0m to run the programme."
BFOOTER = "\033[0;35m➔\033[0;0m type \033[0;34m./pipex_bonus\033[0;0m to run the programme."

all: $(NAME) | footer

header :
	@echo
	@echo $(HEADER)
	@echo

footer :
	@echo $(FOOTER)

bfooter :
	@echo $(BFOOTER)

$(NAME): | header
	@echo "\033[0;35m\033[1m────── making fprintf ──────\033[0;0m"
	@printf "\033[2m"
	@$(MAKE) -C src/fprintf/
	@echo "\033[0;0m"
	@echo "\033[0;35m\033[1m────── making pipex ──────\033[0;0m"
	@printf "\033[2m"
	$(CC) $(FLAGS) -o $(NAME) $(SRC)
	@echo "\033[0;0m"

clean: | header
	@echo "\033[0;35m\033[1m────── clean fprintf ──────\033[0;0m"
	@printf "\033[2m"
	@$(MAKE) clean -C src/fprintf/
	@echo "\033[0;0m"

fclean: clean | header
	@echo "\033[0;35m\033[1m────── fclean pipex ──────\033[0;0m"
	@printf "\033[2m"
	rm -rf $(NAME)
	rm -rf $(BNAME)
	@echo "\033[0;0m"
	@echo "\033[0;35m\033[1m────── fclean fprintf ──────\033[0;0m"
	@printf "\033[2m"
	@$(MAKE) fclean -C src/fprintf/
	@echo "\033[0;0m"

re: fclean all

bonus: $(BNAME) | bfooter

$(BNAME): | header
	@echo "\033[0;35m\033[1m────── making fprintf ──────\033[0;0m"
	@printf "\033[2m"
	@$(MAKE) -C src/fprintf/
	@echo "\033[0;0m"
	@echo "\033[0;35m\033[1m────── making pipex ──────\033[0;0m"
	@printf "\033[2m"
	$(CC) $(FLAGS) -o $(BNAME) $(BSRC)
	@echo


san: | header
	@echo "\033[0;35m\033[1m────── making fprintf ──────\033[0;0m"
	@printf "\033[2m"
	@$(MAKE) -C src/fprintf/
	@echo "\033[0;0m"
	@echo "\033[0;35m\033[1m────── making pipex ──────\033[0;0m"
	@printf "\033[2m"
	$(CC) $(FLAGS) -o $(NAME) $(SRC) -fsanitize=address -g
	@echo
	@echo "\033[0;39m\033[1m(fsanitize build)\033[0;0m"

sre: fclean san

.PHONY: all clean fclean re san sre
	