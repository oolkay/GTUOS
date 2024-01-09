NAME	= olkayos 
FLAGS	= -Wall -Wextra -Werror -std=c++11
CC 		= g++
SRCDIR	= src
SRC		= ${SRCDIR}/Directory.cpp \
			${SRCDIR}/File.cpp \
			${SRCDIR}/LinkedFile.cpp \
			${SRCDIR}/MyOs.cpp \
			${SRCDIR}/RegularFile.cpp \
			${SRCDIR}/main.cpp

OBJDIR	= ./objectives
OBJ		= $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: student $(NAME) run

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $@
	@echo "Compilation has finished succesfully"
	@echo "${NAME} IS READY!!"
	@echo "${NAME} will be executed in 2 seconds..."
	@sleep 2

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@echo "Object files are being deleted"

fclean: clean
	@rm -f $(NAME)
	@echo "Executable file is being deleted"

run:
	@./$(NAME)

re:	fclean all

PHONY: all clean fclean re

student:
	@echo "\n|---------------------------------|"
	@echo "|Name:   Omer Faruk Olkay         |"
	@echo "|Mail:   o.olkay2021@gtu.edu.tr   |"
	@echo "|Number: 210104004039             |"
	@echo "|Have a nice day                  |"
	@echo "|---------------------------------|\n"