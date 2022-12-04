SRC	=	src/*.cpp  	\
		src/Game/*.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	NoelX

CFLAGS 	=  	-Wextra -Wall -g

all:	$(OBJ)
	g++ -o $(NAME) $(OBJ) -l sfml-audio -l sfml-graphics -l sfml-system -l sfml-window

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
