/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:35:36 by asabri            #+#    #+#             */
/*   Updated: 2023/08/22 10:56:57 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sem_error(sem_t *pt)
{
	if (pt == SEM_FAILED)
	{
		kill(0, SIGINT);
	}
}

void	sema_build(t_data *data)
{
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	sem_unlink("/sem_meal");
	data->fork = sem_open("/sem_fork", O_CREAT | O_RDWR,
			0666, data->numb_philos);
	sem_error(data->fork);
	data->print = sem_open("/sem_print", O_CREAT | O_RDWR, 0666, 1);
	sem_error(data->print);
	data->meal = sem_open("/sem_meal", O_CREAT | O_RDWR, 0666, 1);
	sem_error(data->meal);
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
		sema_build(data);
	}
	return (data);
}

void	create_processes(t_philos **philos, t_data *data)
{
	int	i;
	int	status;

	i = -1;
	while (++i < data->numb_philos)
	{
		philos[i]->pid = fork();
		if (!philos[i]->pid)
		{
			monitor_philos(philos[i]);
			exit(0);
		}
	}
	i = -1;
	while (++i < data->numb_philos)
	{
		waitpid(0, &status, 0);
		if (WEXITSTATUS(status) == 1)
			break ;
	}
	kill(0, SIGINT);
}

int	main(int ac, char **av)
{
	t_data		*data;
	t_data		*parser_data;
	t_philos	**philos;

	if (ac < 5 || ac > 6)
		return (write(2, "wrong format\n", 14), 0);
	else
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (0);
		parser_data = parsing(data, av, ac);
		if (!parser_data)
			return (write(2, "Error\n", 7), free(data), 0);
		data = parser_data;
		philos = fill_philo(data);
		create_processes(philos, data);
	}
	return (0);
}
