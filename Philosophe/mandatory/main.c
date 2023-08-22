/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 02:31:26 by asabri            #+#    #+#             */
/*   Updated: 2023/08/22 09:44:13 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ff(void)
{
	system("leaks philo");
}

t_philos	**start_monitoring(t_data *data, t_philos **philos)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * data->numb_philos);
	philos = fill_philo(data, forks);
	i = -1;
	while (++i < data->numb_philos)
		pthread_mutex_init(&forks[i], NULL);
	monitor_philos(philos);
	return (philos);
}

int	main(int ac, char **av)
{
	t_data			*data;
	t_data			*parsed_data;
	t_philos		**philos;
	atexit(ff);
	if (ac < 5 || ac > 6)
		return (write(2, "wrong	format\n", 14), 0);
	else
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (0);
		parsed_data = parsing(data, av, ac);
		if (!parsed_data)
			return (write(2, "Error\n", 7), free(data), 0);
		data = parsed_data;
		philos = NULL;
		philos = start_monitoring(data, philos);
	}
	destroy(philos);
	return (0);
}
