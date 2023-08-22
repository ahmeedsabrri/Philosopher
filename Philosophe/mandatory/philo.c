/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 02:01:28 by asabri            #+#    #+#             */
/*   Updated: 2023/08/16 10:26:59 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philos	**fill_philo(t_data *data, pthread_mutex_t *forks)
{
	t_philos	**philos;
	int			i;

	i = -1;
	philos = malloc(data->numb_philos * sizeof(t_philos *));
	while (++i < data->numb_philos)
	{
		philos[i] = malloc(sizeof(t_philos));
		philos[i]->data = data;
		philos[i]->id = i + 1;
		philos[i]->numb_meals = 0;
		philos[i]->fork = &forks[i];
		philos[i]->next_fork = &(forks[(i + 1) % data->numb_philos]);
	}
	return (philos);
}

t_data	*parsing(t_data *data, char **str, int size)
{
	int	i;

	i = 1;
	while (i < size)
	{
		if (ft_atoi(str[i]) < 0)
			return (NULL);
		(i == 1) && (data->numb_philos = ft_atoi(str[i]), 0);
		(i == 2) && (data->tm_todie = ft_atoi(str[i]), 0);
		(i == 3) && (data->tm_toeat = ft_atoi(str[i]), 0);
		(i == 4) && (data->tm_tosleep = ft_atoi(str[i]), 0);
		if (i == 5 && size == 6)
			data->numb_to_eat = ft_atoi(str[i]);
		else
			data->numb_to_eat = -1;
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->meal, NULL);
	return (data);
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

void	check_died(t_philos **philos)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i >= philos[0]->data->numb_philos)
			i = 0;
		pthread_mutex_lock(&philos[0]->data->meal);
		if (gettimeday() - philos[i]->last_time_eat > 
			(unsigned long) philos[i]->data->tm_todie)
		{
			pthread_mutex_lock(&philos[0]->data->print);
			printf("%ld %d %s\n", gettimeday() - 
				philos[i]->data->start_time, philos[i]->id, "died");
			return ;
		}
		pthread_mutex_unlock(&philos[0]->data->meal);
		if (philos[0]->data->numb_to_eat > 0 && check_meal(philos))
			return ;
		i++;
		usleep(50);
	}
}

void	monitor_philos(t_philos **philos)
{
	int	i;

	i = -1;
	while (++i < philos[0]->data->numb_philos)
		philos[i]->last_time_eat = gettimeday();
	i = -1;
	philos[0]->data->start_time = gettimeday();
	while (++i < philos[0]->data->numb_philos)
		pthread_create(&philos[i]->th, NULL, routine, philos[i]);
	i = -1;
	while (++i < philos[0]->data->numb_philos)
		pthread_detach(philos[i]->th);
	check_died(philos);
}
