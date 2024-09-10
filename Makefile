CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
SOURCES = main.c \
		excute.c \
		free.c \
		init_file.c \
		initialize.c \
		split.c \
		strjoin.c \
		get_next_line.c \
		get_next_line_utils.c \
		putstr.c
B_SOURCES = ./bonus/main_bonus.c \
			./bonus/excute_bonus.c \
			./bonus/free_bonus.c \
			./bonus/init_file_bonus.c \
			./bonus/initialize_bonus.c \
			./bonus/split_bonus.c \
			./bonus/strjoin_bonus.c \
			./bonus/get_next_line_bonus.c \
			./bonus/get_next_line_utils_bonus.c \
			./bonus/putstr_bonus.c

OBJS = $(SOURCES:.c=.o)
B_OBJS = $(B_SOURCES:.c=.o)

ifdef WITH_BONUS
	OBJECTS = $(B_OBJS)
else
	OBJECTS = $(OBJS)
endif

all: $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

bonus :
	make WITH_BONUS=1 all
clean :
	rm -rf $(OBJS) $(B_OBJS)

fclean : clean
	rm -rf $(NAME)
re :
	make fclean
	make all

.PHONY : all clean fclean re bonus