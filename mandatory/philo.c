/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 02:01:28 by asabri            #+#    #+#             */
/*   Updated: 2023/05/20 04:56:43 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
            data->numb_to_eat = 0;
        i++;   
    }
    return (data);
}