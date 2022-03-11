# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/08 15:41:45 by sclam             #+#    #+#              #
#    Updated: 2021/11/07 04:45:45 by sclam            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	ft_atoi.c ft_bzero.c ft_calloc.c \
			ft_strlen.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c \
			ft_memchr.c ft_memcmp.c ft_memcpy.c \
			ft_memmove.c ft_memset.c ft_strchr.c \
			ft_strdup.c ft_striteri.c ft_strjoin.c \
			ft_strlcat.c ft_strlcpy.c ft_strmapi.c \
			ft_strncmp.c ft_strnstr.c ft_strrchr.c \
			ft_substr.c ft_tolower.c ft_toupper.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
			ft_putnbr_fd.c ft_strtrim.c ft_itoa.c ft_split.c

BONUS	=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
			ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
			ft_lstclear.c ft_lstiter.c ft_lstmap.c

NAME	=	libft.a

BON		=	${BONUS:.c=.o}

CC		=	cc

OBJS	=	${SRCS:.c=.o}

ARLIB	=	@ar r

RANLIB	=	ranlib

RM		=	rm -f

HEAD	=	libft.h

%.o : %.c	${HEAD}
			@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${HEAD}
			@${ARLIB} ${NAME} ${OBJS}
			@${RANLIB} ${NAME}

all:		${NAME}

clean:
			@${RM} ${OBJS}
			@${RM} ${BON}

fclean:		clean
			@${RM} ${NAME}

re:			fclean all

bonus:		all
			@make OBJS="${BON}" all

.PHONY:		all clean fclean re