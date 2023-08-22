/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 02:01:13 by asabri            #+#    #+#             */
/*   Updated: 2023/08/22 09:00:54 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_data
{
	int				numb_philos;
	int				tm_todie;
	int				tm_toeat;
	int				tm_tosleep;
	int				numb_to_eat;
	pthread_mutex_t	print;
	pthread_mutex_t	meal;
	unsigned long	start_time;
}					t_data;

typedef struct s_philos
{
	int				id;
	unsigned long	last_time_eat;
	int				numb_meals;
	pthread_t		th;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*next_fork;
	t_data			*data;
}					t_philos;

int				ft_atoi(char *str);
t_data			*parsing(t_data *data, char **str, int size);
t_philos		**fill_philo(t_data *data, pthread_mutex_t *forks);
void			monitor_philos(t_philos **philos);
unsigned long	gettimeday(void);
void			ft_sleep( unsigned long timetodo);
void			printmessege(t_philos *ph, char *msg);
void			eat(t_philos *philo);
int				check_meal(t_philos **ph);
void			destroy(t_philos **philos);
void ft_free(t_data *data);
#endif // !PHILO_H
