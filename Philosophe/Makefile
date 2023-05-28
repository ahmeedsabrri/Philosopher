# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asabri <asabri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 02:02:05 by asabri            #+#    #+#              #
#    Updated: 2023/05/28 16:24:16 by asabri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
BNAME = philo.bonus

CC = cc

FLAGS = -Wall -Werror -Wextra 

RM = rm -rf

SRC = mandatory/atoi.c mandatory/philo.c mandatory/main.c mandatory/philo_utils.c mandatory/destroy.c
BSRC = bonus/atoi.c bonus/philo.c bonus/main.c 

OBJS = $(SRC:.c=.o)
BOBJS = $(BSRC:.c=.o)


all : $(NAME)

mandatory/%.o : mandatory/%.c mandatory/philo.h
			$(CC) $(FLAGS) -o $@ -c $<

bonus/%.o : bonus/%.c bonus/philo.h
			$(CC) $(FLAGS) -o $@ -c $<


$(NAME) : $(OBJS) mandatory/philo.h
			$(CC) $(FLAGS) $(OBJS) -o $@

$(BNAME) : $(BOBJS) bonus/philo.h
			$(CC) $(FLAGS) $(BOBJS) -o $@

bonus : $(BNAME)

clean :
	$(RM) $(OBJS) $(BOBJS)


fclean : clean
	$(RM) $(NAME) $(BNAME)
	

re : fclean all