NAME	 = philo
CFLAGS	 = -Wall -Wextra -Werror -g
SRCS	 = 	philosophers.c\
			philosophers_utils.c\
			free.c\
			init.c\
			lib.c\
			thread.c
OBJS	 = ${SRCS:.c=.o}

%.o: %.c 
	gcc $(CFLAGS) $< -c -o $@ 

$(NAME) : $(OBJS)
	gcc $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

all: $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
