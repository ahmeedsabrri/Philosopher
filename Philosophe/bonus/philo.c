/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:15:35 by asabri            #+#    #+#             */
/*   Updated: 2023/08/14 16:18:57 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philos *philo)
{
	sem_wait(philo->data->fork);
	printmessege(philo, "has taken a fork");
	sem_wait(philo->data->fork);
	printmessege(philo, "has taken a fork");
	printmessege(philo, "is eating");
	ft_sleep(philo->data->tm_toeat);
	sem_wait(philo->data->meal);
	philo->last_time_eat = gettimeday();
	philo->numb_meals++;
	sem_post(philo->data->meal);
	sem_post(philo->data->fork);
	sem_post(philo->data->fork);
}

int	check_meal(t_philos *ph)
{
	int	bol;

	bol = 0;
	sem_wait(ph->data->meal);
	if (ph->data->numb_to_eat >= ph->numb_meals)
		bol = 1;
	sem_post(ph->data->meal);
	if (!bol)
		return (1);
	else
		return (0);
}

void	*routine(void *philos)
{
	t_philos	*ph;
	int			i;

	i = 0;
	ph = philos;
	if (ph->id % 2)
		while (i++ < 500)
			usleep(1);
	while (1)
	{
		eat(ph);
		printmessege(ph, "is sleeping");
		ft_sleep(ph->data->tm_tosleep);
		printmessege(ph, "is thinking");
	}
	return (NULL);
}

void	check_died(t_philos *philos)
{
	while (1)
	{
		usleep(50);
		sem_wait(philos->data->meal);
		if (gettimeday() - philos->last_time_eat >= 
			(unsigned long) philos->data->tm_todie)
		{
			sem_wait(philos->data->print);
			printf("%ld %d %s\n",
				gettimeday() - philos->data->start_time, philos->id, "died");
			exit(1);
		}
		sem_post(philos->data->meal);
		if (philos->data->numb_to_eat > 0 && check_meal(philos))
			exit(1);
	}
}

void	monitor_philos(t_philos *philos)
{
	philos->last_time_eat = gettimeday();
	philos->data->start_time = gettimeday();
	pthread_create(&philos->th, NULL, routine, philos);
	pthread_detach(philos->th);
	check_died(philos);
}
