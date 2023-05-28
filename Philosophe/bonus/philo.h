/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:19:48 by asabri            #+#    #+#             */
/*   Updated: 2023/05/28 17:14:26 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
#include <sys/wait.h>
# include <stdbool.h>
#include <semaphore.h>
#include <signal.h>

typedef struct s_data
{
    int numb_philos;
    int tm_todie;
    int tm_toeat;
    int tm_tosleep;
    int numb_to_eat;
    sem_t *meal;
    sem_t *fork;
    sem_t *print;
    unsigned long start_time;
    
}               t_data;

typedef struct s_philos
{
    pid_t pid;
    int id;
    unsigned long last_time_eat;
    int numb_meals;
    
    pthread_t th;
    t_data *data;
}               t_philos;


int	ft_atoi(char *str);
t_data *parsing(t_data *data, char **str,int size);
t_philos **fill_philo(t_data *data);
void monitor_philos(t_philos *philos);
void check_died(t_philos *philos);
void *routine(void *philos);
int check_meal(t_philos *ph);
void eat(t_philos *philo);
void	ft_sleep( unsigned long timetodo);
void printmessege(t_philos *ph, char *msg);
unsigned long gettimeday();
#endif