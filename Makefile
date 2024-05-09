NAME		=	webserv

CXX	=	c++
CXXFLAGS	=	-Wall -Werror -Wextra -std=c++98
RM			=	rm -rf
SRCS_FOLDER	=	srcs

SRC			=	main.cpp \
				$(SRCS_FOLDER)/Directive.cpp \
				$(SRCS_FOLDER)/Location.cpp \
				$(SRCS_FOLDER)/Methods.cpp \
				$(SRCS_FOLDER)/Parser.cpp \
				$(SRCS_FOLDER)/Processes.cpp \
				$(SRCS_FOLDER)/Requests.cpp \
				$(SRCS_FOLDER)/Server.cpp \
				$(SRCS_FOLDER)/Sockets.cpp

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