NAME		=	webserv

CXX	=	c++
CXXFLAGS	=	-Wall -Werror -Wextra -std=c++98
RM			=	rm -rf
SRCS_FOLDER	=	srcs
CGI_FOLDER	=	cgi-bin

CGI			=	$(SRCS_FOLDER)/Cgi.cpp \
				$(SRCS_FOLDER)/Directive.cpp \
				$(SRCS_FOLDER)/Location.cpp \
				$(SRCS_FOLDER)/Processes.cpp \
				$(SRCS_FOLDER)/Requests.cpp \
				$(SRCS_FOLDER)/Server.cpp \
				$(CGI_FOLDER)/script.cpp

SRC			=	main.cpp \
				$(SRCS_FOLDER)/Directive.cpp \
				$(SRCS_FOLDER)/Location.cpp \
				$(SRCS_FOLDER)/Parser.cpp \
				$(SRCS_FOLDER)/Processes.cpp \
				$(SRCS_FOLDER)/Requests.cpp \
				$(SRCS_FOLDER)/Server.cpp \
				$(SRCS_FOLDER)/Sockets.cpp

OBJ			=	$(SRC:.cpp=.o)
CGI_OBJ		=	$(CGI:.cpp=.o) 

all:		$(NAME)

$(NAME):	$(OBJ) $(CGI_OBJ)
			$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
			$(CXX) $(CXXFLAGS) $(CGI_OBJ) -o script
			mv script $(CGI_FOLDER)/script

clean:
			$(RM) $(OBJ)
			$(RM) $(CGI_OBJ)

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(CGI_FOLDER)/script
			
re:			fclean all

PHONY:		all clean fclean re