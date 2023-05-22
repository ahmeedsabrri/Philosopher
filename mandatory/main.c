/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 02:31:26 by asabri            #+#    #+#             */
/*   Updated: 2023/05/22 05:15:59 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *printthread(void *numb_philo)
{
    printf("had philo %d zaml\n",*(int *)numb_philo);
    return (0);
}

int main(int ac, char **av)
{
    t_data *data;
    pthread_t tr;
    int i;

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
        i = -1;
        while (++i < data->numb_philos)
            pthread_create(&tr,NULL,printthread,&i);
        
    }
    return 0;
}
