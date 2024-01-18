
OBJDIR = obj/

SRCDIR = src/

COLOUR_GREEN=\033[0;32m
COLOUR_PURPLE=\033[0;35m
COLOUR_END=\033[0m
COLOUR_BLUE=\033[0;34
COLOUR_LIGHT_BLUE=\033[1;34
COLOUR_CYAN=\033[0;36
COLOUR_LIGHT_CYAN=\033[1;36

SRC = $(addprefix $(SRCDIR), main.c \
	spawn_threads.c \
	philo_thread.c \
	philo_thread_actions.c \
	philo_thread_helper_functions.c \
	monitor_thread.c \
	monitor_thread_helper_functions.c \
	standard_functions.c \
	helper_functions.c \
	joining_threads.c \
	inits.c)

OBJ = $(addprefix $(OBJDIR), $(notdir $(SRC:.c=.o)))

WAIT_PHILO_DEF = WAIT_PHILO

WAIT_PHILO_SIZE = 1000

GETTING_OUT_OF_BED_DEF = GETTING_OUT_OF_BED

GETTING_OUT_OF_BED_SIZE = 100

NAME = philo

FLAGS = -D$(WAIT_PHILO_DEF)=$(WAIT_PHILO_SIZE) \
		-D$(GETTING_OUT_OF_BED_DEF)=$(GETTING_OUT_OF_BED_SIZE) \
		#-Wall -Werror -Wextra -g -fsanitize=thread -O1

PHILO_H = $(SRCDIR)philosophers.h

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir $(OBJDIR)

$(NAME): $(OBJ) $(PHILO_H)
	@cc $(OBJ) $(FLAGS) -o $(NAME)
	@echo "$(COLOUR_PURPLE)cc $(OBJ) $(FLAGS) -o $(NAME)$(COLOUR_END)\n"

$(OBJ): $(OBJDIR)%.o: $(SRCDIR)%.c
		@cc $(FLAGS) -c $< -o $@
		@echo "$(COLOUR_GREEN)cc $(FLAGS) -c $< -o $@$(COLOUR_END)\n"

clean:
	rm -f $(OBJ)

fclean: clean
	rm $(NAME)

re:
	make clean
	make
