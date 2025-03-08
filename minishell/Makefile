# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naherbal <naherbal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 20:28:19 by naherbal          #+#    #+#              #
#    Updated: 2024/07/20 16:09:31 by naherbal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=	src/main.c								\
		src/history_creation.c					\
		src/second_history_creation.c			\
		src/setup.c								\
		src/free_data.c							\
		src/path_exec.c							\
		src/secure_path.c						\
		src/expr.c								\
		src/quotes_handling.c					\
		src/echo_dollar.c						\
		src/check_pipes_redirections_quotes.c	\
		src/pipes.c								\
		src/second_pipes.c						\
		src/third_pipes.c						\
		src/redirection.c						\
		src/second_redirection.c				\
		src/spec_echo.c							\
		src/fcts_array.c						\
		src/second_fcts_array.c					\
		src/built/built_in.c					\
		src/built/second_built_in.c				\
		src/built/third_built_in.c				\
		src/built/quotes_built_in.c				\
		src/built/export.c						\
		src/built/second_export.c				\
		src/built/unset.c						\
		src/built/ft_echo.c						\
		src/built/ft_cd.c						\
		src/built/print_history.c				\
		src/fcts/ft_strjoin.c					\
		src/fcts/ft_split.c						\
		src/fcts/ft_putstr_fd.c					\
		src/fcts/ft_strlcpy.c					\
		src/fcts/ft_putnbr_fd.c					\
		src/fcts/ft_strncmp.c					\
		src/fcts/check_substr.c					\
		src/fcts/ft_substr.c					\
		src/fcts/ft_memdel.c					\
		src/fcts/ft_itoa.c						\
		src/fcts/ft_putendl_fd.c				\

OBJ		=	$(SRC:.c=.o)

NAME	=	minishell

INCL_RL = /usr/local/opt/readline/include/

LINK_RL = /usr/local/opt/readline/lib -L/usr/local/Cellar/readline/8.1.2/lib -I/usr/local/Cellar/readline/8.1.2/include

CFLAGS	=	-Wall -Wextra -Werror -g
# CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address
# const char* __asan_default_options() { return "detect_leaks=0"; } to remove leaks from -fsanitize=address
# export ASAN_OPTIONS=detect_leaks=0
HEADERS	=	-I include

RM		=	rm -rf

all:	$(NAME)

$(NAME):
		cc $(CFLAGS) $(SRC) -lreadline -I $(LINK_RL) -I $(INCL_RL) -o $(NAME)

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re
