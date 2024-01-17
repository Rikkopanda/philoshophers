
OBJDIR = obj/

SRCDIR = src/

COLOUR_GREEN=\033[0;32m
COLOUR_END=\033[0m

SRC = $(addprefix $(SRCDIR), main.c \
			standard_functions1.c \
			standard_functions2.c \
			init_main_process.c \
			helper_functions.c \
			sem_helper_functions.c \
			terminating.c \
			philo_process.c \
			philo_init.c \
			philo_monitor.c \
			philo_monitor_helper_functions.c \
			philo_activities.c \
			philo_helper_functions.c)

OBJ = $(addprefix $(OBJDIR), $(notdir $(SRC:.c=.o)))

NAME = philo

WAIT_PHILO_DEF = WAIT_PHILO

WAIT_PHILO_SIZE = 1000

FLAGS = -D$(WAIT_PHILO_DEF)=$(WAIT_PHILO_SIZE) -g -fsanitize=thread -O2 #-g -fsanitize=address #-Wall -Werror -Wextra 

PHILO_H = $(SRCDIR)philosophers.h

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir $(OBJDIR)

$(NAME): $(OBJ) $(PHILO_H)
	cc $(OBJ) $(FLAGS) -o $(NAME)

$(OBJ): $(OBJDIR)%.o: $(SRCDIR)%.c
		cc $(FLAGS) -c $< -o $@
		@echo "$(COLOUR_GREEN)testing colour$(COLOUR_END)\n"

clean:
	rm -f $(OBJ)

fclean: clean
	rm $(NAME)

re:
	make clean
	make
