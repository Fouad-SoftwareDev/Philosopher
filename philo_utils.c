/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:45:08 by fdahouk           #+#    #+#             */
/*   Updated: 2024/12/24 23:11:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((unsigned long)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

int	ft_atoi(char *nptr)
{
	int	count;
	int	sign;
	int	i;
	int	res;

	res = 0;
	count = 0;
	i = 0;
	sign = 1;
	while (nptr[i] != '\0' && (nptr[i] == ' '
			|| (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	while (nptr[i] != '\0' && (nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		count++;
		if (count == 2)
			return (res);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		res = res * 10 + (nptr[i++] - '0');
	return (res * sign);
}

void	destroy_mutex(t_myenv *env)
{
	int	i;

	i = 0;
	while (i < env->philocount)
	{
		pthread_mutex_destroy(&env->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&env->writingM);
}

int	check_arg_validity(char	**argv, int argc, t_myenv *myenv)
{
	myenv->philocount = ft_atoi(argv[1]);
	myenv->time_to_die = ft_atoi(argv[2]);
	myenv->time_to_eat = ft_atoi(argv[3]);
	myenv->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		myenv->max_timestoeat = ft_atoi(argv[5]);
	else
		myenv->max_timestoeat = -1;
	if (myenv->philocount < 1 || myenv->time_to_die < 0
		|| myenv->time_to_eat < 0
		|| myenv->time_to_sleep < 0 || (ft_atoi(argv[5]) <= 0) && argc == 6)
		return (1);
	return (0);
}

void	*handler(void *arg)
{
	// the main thread function to write
}
