/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 02:31:26 by asabri            #+#    #+#             */
/*   Updated: 2023/05/20 04:56:54 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_data *data;
    int i;

    i = 1;
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
    }
    return 0;
}
