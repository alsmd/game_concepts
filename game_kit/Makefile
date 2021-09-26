SRCS = game_kit.c

OBJS = $(SRCS:.c=.o)

NAME = libgame.a

CFLAGS		= -g -Wall -Werror -Wextra

CC = clang

RM = rm -f

all: $(NAME)


$(NAME): $(OBJS)
	make -C ../vec_lib
	mv ../vec_lib/libvec.a $(NAME)
	ar rc $(NAME) $(OBJS)
clean:
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re: fclean all