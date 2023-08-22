/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 11:14:32 by asabri            #+#    #+#             */
/*   Updated: 2023/08/22 09:04:25 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(t_philos **philos)
{
	int	i;

	i = -1;
	while (++i < philos[0]->data->numb_philos)
	{
		pthread_mutex_destroy(&philos[i]->data->print);
		pthread_mutex_destroy(&philos[i]->data->meal);
		pthread_mutex_destroy(philos[i]->fork);
		pthread_mutex_destroy(philos[i]->next_fork);
	}
	free(philos);
}
void ft_free(t_data *data)
{
	// free(&data->numb_philos);
	// free(&data->tm_todie);
	// free(&data->tm_toeat);
	// free(&data->tm_tosleep);
	// free(&data->numb_to_eat);
	// free(&data->print);
	// free(&data->meal);
	// free(&data->start_time);
	free(data);
}
