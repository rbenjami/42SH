# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/26 13:13:47 by rbenjami          #+#    #+#              #
#    Updated: 2014/03/14 12:29:14 by rbenjami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include		libft/Makefile.sources

export	CFLAGS	=	-Wall -Wextra -Werror -g

export	CC		=	cc

export	INC		=	-I $(PWD)/libft

NAME		=	42SH

INC			+=	-I includes

HEAD		=	includes/sh.h

SRC_DIR		=	srcs/

BUI_DIR		=	$(SRC_DIR)builtin/

FILES		=	main.c			\
				lexer_is.c		\
				ast.c			\
				token.c			\
				execute.c		\
				error.c			\
				pipe.c			\
				find_op.c		\
				lexer.c			\
				parse_string.c	\
				ft_getenv.c		\
				utils.c			\
				operator.c		\
				redir.c

BUI_FILES	=	builtin.c		\
				cd.c			\
				exit.c			\
				setenv.c		\
				unsetenv.c		\
				env.c			\
				echo.c

SRC			=	$(addprefix $(SRC_DIR), $(FILES))\
				$(addprefix $(BUI_DIR), $(BUI_FILES))

OBJ			=	$(SRC:.c=.o)

LIB			=	-L./ -lft

OBJ_LIB		=	$(libft/SRC_LIB:.c=.o)

HEAD_LIB	=	libft/libft.h libft/get_next_line.h libft/define_type.h

all:			libft.a $(NAME)

libft.a:		libft/$(OBJ_LIB) $(HEAD_LIB)
	@make -C libft

$(NAME):		$(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)
	@echo ""
	@echo "\033[33m"compilation of $(NAME) : "\033[32m"Success"\033[0m"

$(OBJ):			$(HEAD) libft.a

%.o:			%.c $(HEAD)
	@echo -n .
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	@/bin/rm -f $(OBJ)
	@echo "\033[31m"Objects of $(NAME) : deleted"\033[0m"

fclean:			clean
	@/bin/rm -f $(NAME)
	@echo "\033[31m"$(NAME) : deleted"\033[0m"
	@make fclean -C libft
re:				fclean all

.PHONY:			all clean fclean re
