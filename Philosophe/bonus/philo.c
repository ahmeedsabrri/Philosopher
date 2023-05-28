/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:15:35 by asabri            #+#    #+#             */
/*   Updated: 2023/05/28 17:58:56 by asabri           ###   ########.fr       */
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
    sem_wait(ph->data->print);
    printf("%ld %d %s\n",gettimeday() - ph->data->start_time,ph->id,msg);
    sem_post(ph->data->print);
}

void	ft_sleep( unsigned long timetodo)
{
	unsigned long	time;

	time = gettimeday();
    
	while (gettimeday() - time < timetodo)
		usleep(50);
}

t_philos **fill_philo(t_data *data)
{
    t_philos **philos;
    int i;
    
    i = -1;
    philos = malloc(data->numb_philos * sizeof(t_philos *));
    while (++i < data->numb_philos)
    {
        philos[i] = malloc(sizeof(t_philos));
        philos[i]->data = data;
        philos[i]->id = i + 1;
        philos[i]->numb_meals = 0;
    }
    return (philos);
}
void sem_error(sem_t *pt)
{
    if (pt == SEM_FAILED)
    {
        kill(0, SIGINT);
    }
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
    sem_unlink("/sem_fork");
    sem_unlink("/sem_print");
    sem_unlink("/sem_meal");
    data->fork = sem_open("/sem_fork",O_CREAT | O_RDWR,0666,data->numb_philos);
      sem_error(data->fork);
    data->print = sem_open("/sem_print",O_CREAT | O_RDWR ,0666,1);
      sem_error(data->print);
    data->meal = sem_open("/sem_meal",O_CREAT | O_RDWR ,0666,1);
      sem_error(data->meal);
    return (data);
}

void eat(t_philos *philo)
{
    sem_wait(philo->data->fork);
    printmessege(philo,"has taken a fork");
    sem_wait(philo->data->fork);
    printmessege(philo,"has taken a fork");
    
    printmessege(philo,"is eating");
    ft_sleep(philo->data->tm_toeat);
    sem_wait(philo->data->meal);
    philo->last_time_eat = gettimeday();
    philo->numb_meals++;
    sem_post(philo->data->meal);
    sem_post(philo->data->fork);
    sem_post(philo->data->fork);
    
}

int check_meal(t_philos *ph)
{
    int bol;

    bol = 0;
    sem_wait(ph->data->meal);
    if (ph->data->numb_to_eat >= ph->numb_meals)
            bol = 1;
    sem_post(ph->data->meal);
    if(!bol)
        return(1);
    else
        return (0);
}
void *routine(void *philos)
{
    t_philos * ph = philos;
    int i =0;
    if(ph->id % 2)
        while(i++ < 500)
            usleep(1);   
    while (1)
    {
        eat(ph);
        printmessege(ph,"is sleeping");
        ft_sleep(ph->data->tm_tosleep);
        printmessege(ph,"is thinking");
    }
    return(NULL);
}

void check_died(t_philos *philos)
{
    while (1)
    {
    usleep(50);
    sem_wait(philos->data->meal);
    if(gettimeday() - philos->last_time_eat >= (unsigned long) philos->data->tm_todie)
    {
        sem_wait(philos->data->print);
        printf("%ld %d %s\n",gettimeday() -  philos->data->start_time,philos->id,"died");
        exit(1);
    }
    sem_post(philos->data->meal);
    if(philos->data->numb_to_eat > 0 && check_meal(philos))
        exit(1) ;
    }
    
}

void monitor_philos(t_philos *philos)
{
    
    philos->last_time_eat = gettimeday();
    philos->data->start_time = gettimeday();
    pthread_create(&philos->th, NULL, routine,philos);
    pthread_detach(philos->th);
    check_died(philos);
}