SRCS =	main.c aux.c pixel_manipulation.c

OBJS = $(SRCS:.c=.o)

NAME = play

CFLAGS		= -g

VEC_LIB_DIR = ../game_kit

FLAGS		= -ldl -Imlx -Lmlx -lmlx -lm -lbsd -lXext -lX11

CC = clang

RM = rm -f

all: $(NAME)

.c.o:
	${CC} ${CFLAGS} -Imlx -Ibass -c $< -o ${<:.c=.o}

$(NAME): make_lib $(OBJS)
	make -C mlx
	${CC} $(CFLAGS) -o $(NAME) $(OBJS) $(FLAGS) -L$(VEC_LIB_DIR) -lgame

clean:
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)
make_lib:
	make -C $(VEC_LIB_DIR)
run: $(NAME)
	./$(NAME)
re: fclean all