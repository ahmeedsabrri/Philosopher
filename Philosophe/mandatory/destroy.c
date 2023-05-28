/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 11:14:32 by asabri            #+#    #+#             */
/*   Updated: 2023/05/28 11:18:52 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void destroy(t_philos **philos)
{
    int i;
    
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