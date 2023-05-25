/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 02:39:42 by asabri            #+#    #+#             */
/*   Updated: 2023/05/25 15:46:02 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char *c)
{
	int	i;

	i = 0;
	if (!*c)
		return (1);
	while (c[i])
	{
		if ((c[i] < '0' || c[i] > '9'))
			return (1);
		i++;
	}
	return (0);
}


int	ft_atoi(char *str)
{
	long	res;
	int	sign;

	res = 0;
	sign = 1;
	
	
	while (*str == 32)
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	if (ft_isdigit(str))
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
		if (res > 2147483647)
			return (-1);	
	}
	if (res == 0)
		return (-1);
	return (res * sign);
}