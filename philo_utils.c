/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:45:08 by fdahouk           #+#    #+#             */
/*   Updated: 2025/01/07 18:38:45 by marvin           ###   ########.fr       */
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
	pthread_mutex_destroy(&env->writing_m);
	pthread_mutex_destroy(&env->meal_m);
	pthread_mutex_destroy(&env->death_m);
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
		|| myenv->time_to_sleep < 0
		|| ((myenv->max_timestoeat <= 0) && argc == 6))
		return (1);
	return (0);
}

void	*handler(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (1)
	{
		if (someone_died(ph))
			break;
		take_forks(ph);
		eat(ph);
		sleeping(ph);
		thinking(ph);
	}
	return (NULL);
}

void	take_forks(t_philo *ph)
{
	if (ph->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&ph->env->forks[ph->forkone]);
		custom_print(" has taken a fork", ph);
		pthread_mutex_lock(&ph->env->forks[ph->forktwo]);
		custom_print(" has taken a fork", ph);
	}
	else
	{
		usleep(100);
		pthread_mutex_lock(&ph->env->forks[ph->forktwo]);
		custom_print(" has taken a fork", ph);
		pthread_mutex_lock(&ph->env->forks[ph->forkone]);
		custom_print(" has taken a fork", ph);
	}
}
