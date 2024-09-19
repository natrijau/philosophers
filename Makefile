NAME	 = philo
CFLAGS	 = -Wall -Wextra -Werror ## -g -gdwarf-4 -lpthread
SRCS	 = 	philosophers.c\
			philosophers_utils.c\
			free.c\
			init.c\
			lib.c\
			thread.c\
			thread_utils.c
OBJS	 = ${SRCS:.c=.o}

%.o: %.c 
	cc $(CFLAGS) $< -c -o $@ 

$(NAME) : $(OBJS)
	cc $(CFLAGS) -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
