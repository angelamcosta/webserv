NAME		=	webserv

CXX	=	c++
CXXFLAGS	=	-Wall -Werror -Wextra -g -std=c++98
RM			=	rm -rf
SRCS_FOLDER	=	srcs
PY_CACHE	=	cgi-bin/__pycache__

CLEAR		= \033[0m
PINK 		= \033[38;5;206m
LAVENDER 	= \033[38;5;183m
MINT 		= \033[38;5;121m
PEACH 		= \033[38;5;223m
SKYBLUE 	= \033[38;5;117m
YELLOW 		= \033[38;5;226m
HEART 		= ♡
FLOWER 		= ❀

SRC			=	main.cpp \
				$(SRCS_FOLDER)/Directive.cpp \
				$(SRCS_FOLDER)/Location.cpp \
				$(SRCS_FOLDER)/Parser.cpp \
				$(SRCS_FOLDER)/Processes.cpp \
				$(SRCS_FOLDER)/Requests.cpp \
				$(SRCS_FOLDER)/Server.cpp \
				$(SRCS_FOLDER)/Sockets.cpp \
				$(SRCS_FOLDER)/Stack.cpp


OBJ			=	$(SRC:.cpp=.o)

%.o : %.cpp
			@$(CXX) -c $(CXXFLAGS) $< -o $@

all:		$(NAME)

$(NAME):	out_obj $(OBJ)
			@echo "$(PEACH)$(HEART) Creating all resources $(HEART)$(CLEAR)"
			@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
			@cd cgi-bin && chmod 777 *.py
			@cd public/images && chmod 644 *

clean:
			@$(RM) $(OBJ)

fclean:		clean
			@echo "$(MINT)$(FLOWER) Cleaning all resources $(FLOWER)$(CLEAR)"
			@$(RM) $(NAME)
			@$(RM) $(PY_CACHE)
			
re:			fclean all

out_obj:	
			@echo "$(LAVENDER)$(HEART) Creating all objects $(HEART)$(CLEAR)"

PHONY:		all clean fclean re
