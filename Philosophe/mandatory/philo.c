/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 02:01:28 by asabri            #+#    #+#             */
/*   Updated: 2023/05/25 19:04:16 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philos **fill_philo(t_data *data,pthread_mutex_t *forks)
{
    t_philos **philos;
    int i;
    
    i = -1;
    philos = malloc(data->numb_philos * sizeof(t_philos *));
    while (++i < data->numb_philos)
    {
        philos[i] = malloc(sizeof(t_philos));
        philos[i]->data = data;
        philos[i]->id = i+1;
        philos[i]->numb_meals = 0;
        philos[i]->fork = &forks[i];
        philos[i]->next_fork = &(forks[(i + 1) % data->numb_philos]);
    }
    return (philos);
}

t_data *parsing(t_data *data, char **str,int size)
{
    int i;
    i = 1;
    while (i < size)
    {
        if (ft_atoi(str[i]) < 0)
            return (NULL);
        (i == 1) && (data->numb_philos = ft_atoi(str[i]),0);
        (i == 2) && (data->tm_todie = ft_atoi(str[i]),0);
        (i == 3) && (data->tm_toeat = ft_atoi(str[i]),0);
        (i == 4) && (data->tm_tosleep = ft_atoi(str[i]),0);
        if (i == 5 && size == 6)
            data->numb_to_eat = ft_atoi(str[i]);
        else
            data->numb_to_eat = -1;
        i++;   
    }
    data->start_time = gettimeday();
    pthread_mutex_init(&data->print,NULL);
    pthread_mutex_init(&data->meal,NULL);
    return (data);
}
void	ft_sleep( unsigned long timetodo)
{
	unsigned long	time;

	time = gettimeday();
    
	while (gettimeday() - time < timetodo)
		usleep(50);
}

void printmessege(t_philos *ph, char *msg)
{
    pthread_mutex_lock(&ph->data->print);
    printf("%ld %d %s\n",gettimeday() - ph->data->start_time,ph->id,msg);
    pthread_mutex_unlock(&ph->data->print);
}

void eat(t_philos *philo)
{
    pthread_mutex_lock(philo->fork);
    printmessege(philo,"has taken a fork");
    pthread_mutex_lock(philo->next_fork);
    printmessege(philo,"has taken a fork");
    printmessege(philo,"is eating");
    ft_sleep(philo->data->tm_toeat);
    pthread_mutex_lock(&philo->data->meal);
    philo->last_time_eat = gettimeday();
    philo->numb_meals++;
    pthread_mutex_unlock(&philo->data->meal);
    pthread_mutex_unlock(philo->next_fork);
    pthread_mutex_unlock(philo->fork);
}

void *routine(void *philos)
{
    t_philos * ph = philos;
    if(ph->id % 2)
        usleep(500);
    while (1)
    {
        eat(ph);
        printmessege(ph,"is sleeping");
        ft_sleep(ph->data->tm_tosleep);
        printmessege(ph,"is thinking");
    }    
    return(NULL);
}

unsigned long gettimeday()
{
    struct  timeval time;
    unsigned long currentte;
    gettimeofday(&time,NULL);
    currentte = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return (currentte);    
}


int check_meal(t_philos **ph)
{
    int i;
    int bol;

    bol = 0;
    i = -1;
    while (++i < ph[0]->data->numb_philos)
    {
        if (ph[0]->data->numb_to_eat >= ph[i]->numb_meals)
                bol = 1;
    }
    if(!bol)
        return(1);
    else
        return (0);
}

void monitor_philos(t_philos **philos)
{
    int i;

    i = -1;
    while(++i < philos[0]->data->numb_philos)
        philos[i]->last_time_eat = gettimeday();
    i = -1;
    while (++i < philos[0]->data->numb_philos)
        pthread_create(&philos[i]->th, NULL, routine,philos[i]);
    i = -1;
    while (++i < philos[0]->data->numb_philos)
        pthread_detach(philos[i]->th);
    i = 0;
    while (1)
    {
        pthread_mutex_lock(&philos[0]->data->meal);
        if(i>= philos[0]->data->numb_philos)
            i = 0;
        if(gettimeday() - philos[i]->last_time_eat > (unsigned long) philos[i]->data->tm_todie)
        {
            pthread_mutex_lock(&philos[0]->data->print);
             printf("%ld %d %s\n",gettimeday() -  philos[i]->data->start_time,philos[i]->id,"died");
             return ;
        }
        if(philos[0]->data->numb_to_eat > 0 && check_meal(philos))
            return ;
        i++;
        pthread_mutex_unlock(&philos[0]->data->meal);
    }
    
}