/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 02:01:13 by asabri            #+#    #+#             */
/*   Updated: 2023/05/20 04:57:48 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_philos
{
    
    struct s_philos *next;
}               t_philos;

typedef struct s_data
{
    int numb_philos;
    int tm_todie;
    int tm_toeat;
    int tm_tosleep;
    int numb_to_eat;
}               t_data;


int	ft_atoi(char *str);
t_data *parsing(t_data *data, char **str,int size);
#endif // !PHILO_H
