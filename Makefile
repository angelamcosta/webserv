NAME		=	webserv

CXX	=	c++
CXXFLAGS	=	-Wall -Werror -Wextra -g -std=c++98
RM			=	rm -rf
SRCS_FOLDER	=	srcs
PY_CACHE	=	cgi-bin/__pycache__

SRC			=	main.cpp \
				$(SRCS_FOLDER)/Directive.cpp \
				$(SRCS_FOLDER)/Location.cpp \
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
			$(RM) $(PY_CACHE)
			
re:			fclean all

PHONY:		all clean fclean re
