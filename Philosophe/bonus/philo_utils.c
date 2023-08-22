/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:24:40 by asabri            #+#    #+#             */
/*   Updated: 2023/08/14 16:18:39 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philos	**fill_philo(t_data *data)
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
	}
	return (philos);
}

unsigned long	gettimeday(void)
{
	struct timeval	time;
	unsigned long	currentte;

	gettimeofday(&time, NULL);
	currentte = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (currentte);
}

void	printmessege(t_philos *ph, char *msg)
{
	sem_wait(ph->data->print);
	printf("%ld %d %s\n", gettimeday() - ph->data->start_time, ph->id, msg);
	sem_post(ph->data->print);
}

void	ft_sleep( unsigned long timetodo)
{
	unsigned long	time;

	time = gettimeday();
	while (gettimeday() - time < timetodo)
		usleep(50);
}
