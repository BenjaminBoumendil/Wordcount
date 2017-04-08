NAME		=		wordcount

INCLUDE_DIR	=		includes

SRC_DIR		=		srcs

SRC			=		main.c				\
					get_next_line.c		\
					parse_dictfile.c	\
					parse_inputfile.c	\
					list.c				\
					print.c

OBJ			=		$(SRC:.c=.o)

FLAG_COMP	=		-g -Wall -Wextra -Werror -I$(INCLUDE_DIR)

all:
	$(MAKE) $(NAME)

$(NAME): $(OBJ)
	gcc -o $@ $^

%.o: $(SRC_DIR)/%.c
	gcc -c $(FLAG_COMP) $^

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all
