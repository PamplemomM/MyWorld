##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## The makefile to compile the project.
##

NAME	=	my_world

SRCS	=	$(shell find . -type f -name '*.c')

FLAGS	=	-l csfml-graphics -l csfml-system -l csfml-audio -lcsfml-window -lm

all	:	$(NAME)

$(NAME)	:
		gcc -o $(NAME) $(SRCS) $(FLAGS)

clean	:
		rm -rf $(NAME)

fclean	:	clean

re	:	fclean	all
