NAME		=	webserv

CXX	=	c++
CXXFLAGS	=	-Wall -Werror -Wextra -std=c++98
RM			=	rm -rf
SRCS_FOLDER	=	srcs

SRC			=	main.cpp \
				$(SRCS_FOLDER)/processes.cpp \
				$(SRCS_FOLDER)/requests.cpp \
				$(SRCS_FOLDER)/sockets.cpp \
				$(SRCS_FOLDER)/static_files.cpp

OBJ			=	$(SRC:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)
			
re:			fclean all

PHONY:		all clean fclean re