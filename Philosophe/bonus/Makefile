# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asabri <asabri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 02:02:05 by asabri            #+#    #+#              #
#    Updated: 2023/08/06 17:19:10 by asabri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BNAME = philo

CC = cc

FLAGS = -Wall -Werror -Wextra 

RM = rm -rf

BSRC = atoi.c philo.c main.c 

BOBJS = $(BSRC:.c=.o)


all : $(BNAME)


%.o : %.c philo.h
			$(CC) $(FLAGS) -o $@ -c $<

$(BNAME) : $(BOBJS) philo.h
			$(CC) $(FLAGS) $(BOBJS) -o $@

clean :
	$(RM) $(BOBJS)


fclean : clean
	$(RM) $(BNAME)
	

re : fclean all