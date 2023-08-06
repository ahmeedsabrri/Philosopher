/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 02:31:26 by asabri            #+#    #+#             */
/*   Updated: 2023/06/05 16:02:25 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ff()
{
    system("leaks philo");
}
int main(int ac, char **av)
{
    t_data *data;
    pthread_mutex_t *forks;
    t_philos **philos;
    int i;

    //atexit(ff);
    data = malloc(sizeof(t_data));
    if (!data)
        return (0);
    if (ac < 5 || ac > 6)
        return (write(2, "wrong format\n",14), 0);
    else
    {
        data = parsing(data,av,ac);
        if (!data)
            return (write(2,"Error\n", 7), 0);
        forks = malloc(sizeof(pthread_mutex_t) * data->numb_philos);
        philos = fill_philo(data, forks);
        i = -1;
        while (++i < data->numb_philos)
            pthread_mutex_init(&forks[i],NULL);
        monitor_philos(philos);
    }
    destroy(philos);
    return 0;
}
