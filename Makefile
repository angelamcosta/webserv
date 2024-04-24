NAME		=	webserv

CXX	=	c++
CXXFLAGS	=	-Wall -Werror -Wextra -std=c++98
RM			=	rm -rf
SRCS_FOLDER	=	srcs

SRC			=	main.cpp \
				$(SRCS_FOLDER)/parser/Directive.cpp \
				$(SRCS_FOLDER)/parser/Location.cpp \
				$(SRCS_FOLDER)/parser/Server.cpp \
				$(SRCS_FOLDER)/parser/parser.cpp \
				$(SRCS_FOLDER)/aux_funcs.cpp \
				$(SRCS_FOLDER)/processes.cpp \
				$(SRCS_FOLDER)/requests.cpp \
				$(SRCS_FOLDER)/sockets.cpp

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