# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 15:32:55 by sclam             #+#    #+#              #
#    Updated: 2021/11/07 04:45:11 by sclam            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	ft_pipex.c \
			ft_pipex_one_com.c \
			main.c

LIBFT	=	-L./libft -lft

NAME	= pipex

CC		= cc

OBJS	= ${SRCS:.c=.o}

RM		= rm -f

HEAD	= pipex.h

%.o : %.c	${HEAD}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${HEAD}
			make bonus -C ./libft
			${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LIBFT}

all:		${NAME}

clean:
			${RM} ${OBJS}
			make clean -C ./libft

fclean:		
			${RM} ${OBJS}
			${RM} ${NAME}
			make fclean -C ./libft

re:			fclean all

.PHONY:		all clean fclean re