/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:35:36 by asabri            #+#    #+#             */
/*   Updated: 2023/05/28 17:53:13 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_data *data;
    t_philos **philos;
    int i;
    int status;

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
        philos = fill_philo(data);
        i = -1;
        while(++i < data->numb_philos)
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
            waitpid(0,&status,0);
            if (WEXITSTATUS(status) == 1)
                break;
        }
        kill(0,SIGINT);
    }
    return 0;
}
