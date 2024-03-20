NAME	 = philosophers
CFLAGS	 = -Wall -Wextra -Werror -g
SRCS	 = philosophers.c philosophers_utils.c initialize.c 
OBJS	 = ${SRCS:.c=.o}

%.o: %.c 
	clang $(CFLAGS) $< -c -o $@ 

$(NAME) : $(OBJS)
	clang -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

all: $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
