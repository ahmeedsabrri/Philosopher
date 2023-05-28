/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:02:27 by asabri            #+#    #+#             */
/*   Updated: 2023/05/28 10:58:43 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long gettimeday()
{
    struct  timeval time;
    unsigned long currentte;
    gettimeofday(&time,NULL);
    currentte = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return (currentte);    
}

void printmessege(t_philos *ph, char *msg)
{
    pthread_mutex_lock(&ph->data->print);
    printf("%ld %d %s\n",gettimeday() - ph->data->start_time,ph->id,msg);
    pthread_mutex_unlock(&ph->data->print);
}

void	ft_sleep( unsigned long timetodo)
{
	unsigned long	time;

	time = gettimeday();
    
	while (gettimeday() - time < timetodo)
		usleep(50);
}

void eat(t_philos *philo)
{
    pthread_mutex_lock(philo->fork);
    printmessege(philo,"has taken a fork");
    pthread_mutex_lock(philo->next_fork);
    printmessege(philo,"has taken a fork");
    printmessege(philo,"is eating");
    ft_sleep(philo->data->tm_toeat);
    pthread_mutex_unlock(philo->next_fork);
    pthread_mutex_unlock(philo->fork);
    pthread_mutex_lock(&philo->data->meal);
    philo->last_time_eat = gettimeday();
    philo->numb_meals++;
    pthread_mutex_unlock(&philo->data->meal);
}

int check_meal(t_philos **ph)
{
    int i;
    int bol;

    bol = 0;
    i = -1;
    pthread_mutex_lock(&ph[0]->data->meal);
    while (++i < ph[0]->data->numb_philos)
    {
        if (ph[0]->data->numb_to_eat >= ph[i]->numb_meals)
                bol = 1;
    }
    pthread_mutex_unlock(&ph[0]->data->meal);
    if(!bol)
        return(1);
    else
        return (0);
}