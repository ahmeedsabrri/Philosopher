# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asabri <asabri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 02:02:05 by asabri            #+#    #+#              #
#    Updated: 2023/08/22 09:51:55 by asabri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

FLAGS = -Wall -Werror -Wextra -fsanitize=thread

RM = rm -rf

SRC = atoi.c philo.c main.c philo_utils.c destroy.c


OBJS = $(SRC:.c=.o)


all : $(NAME)

%.o : %.c philo.h
		$(CC) $(FLAGS) -o $@ -c $<

$(NAME) : $(OBJS) philo.h
			$(CC) $(FLAGS) $(OBJS) -o $@


clean :
	$(RM) $(OBJS) $(BOBJS)


fclean : clean
	$(RM) $(NAME) $(BNAME)
	

re : fclean all