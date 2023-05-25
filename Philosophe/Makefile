# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asabri <asabri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 02:02:05 by asabri            #+#    #+#              #
#    Updated: 2023/05/25 18:33:53 by asabri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

FLAGS = -Wall -Werror -Wextra -g

RM = rm -rf

SRC = mandatory/atoi.c mandatory/philo.c mandatory/main.c
OBJS = $(SRC:.c=.o)

all : $(NAME)

mandatory/%.o : mandatory/%.c mandatory/philo.h
			$(CC) $(FLAGS) -o $@ -c $<


$(NAME) : $(OBJS) mandatory/philo.h
			$(CC) $(FLAGS) $(OBJS) -o $@

clean :
	$(RM) $(OBJS) 


fclean : clean
	$(RM) $(NAME) 
	

re : fclean all