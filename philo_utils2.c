/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:24:48 by fdahouk           #+#    #+#             */
/*   Updated: 2025/01/08 00:08:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*handler1(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	pthread_mutex_lock(&ph->env->forks[0]);
	custom_print(" has taken a fork", ph);
	usleep(ph->env->time_to_die * 1000);
	custom_print(" has died", ph);
	pthread_mutex_unlock(&ph->env->forks[0]);
	return (NULL);
}

void	clean_memory(t_myenv *env)
{

	destroy_mutex(env);
	if (env->forks)
		free(env->forks);
	if (env->ph)
		free(env->ph);
}

void	eat(t_philo *ph)
{
	unsigned long	time;

	pthread_mutex_lock(&ph->env->meal_m);
	if (someone_died(ph))
	{
		pthread_mutex_unlock(&ph->env->meal_m);
		pthread_mutex_unlock(&ph->env->forks[ph->forkone]);
		pthread_mutex_unlock(&ph->env->forks[ph->forktwo]);
		return ;
	}
	time = get_time_in_ms();
	ph->last_meal_time = time;
	custom_print(" is eating", ph);
	ph->eatcount += 1;
	pthread_mutex_unlock(&ph->env->meal_m);
	usleep((ph->env->time_to_eat) * 1000);
	pthread_mutex_unlock(&ph->env->forks[ph->forkone]);
	pthread_mutex_unlock(&ph->env->forks[ph->forktwo]);
}

void	monitor_death(t_myenv *env)
{
	int	i;

	while(1)
	{
		i = 0;
		if (env->philocount == 1)
			return ;
		while (i < env->philocount)
		{
			if (check_philosopher(&env->ph[i]))
				return ;
			i++;
		}
		if (check_eatcount(env))
			return ;
		usleep(100);
	}
}

int	check_philosopher(t_philo *ph)
{
	unsigned long	time;

	pthread_mutex_lock(&ph->env->meal_m);
	time = get_time_in_ms();
	if ((time - ph->last_meal_time) > (unsigned long)ph->env->time_to_die)
	{
		if (ph->env->stop_death == 0)
		{
			pthread_mutex_lock(&ph->env->death_m);
			time = (get_time_in_ms() - ph->env->start_time);
			printf("%lu  %d has died \n", time, ph->philo_id);
			ph->env->stop_death = 1;
			pthread_mutex_unlock(&ph->env->death_m);
			pthread_mutex_unlock(&ph->env->meal_m);
			return (1);
		}
	}
	pthread_mutex_unlock(&ph->env->meal_m);
	return (0);
}

void	sleeping(t_philo *philo)
{
	custom_print(" is sleeping", philo);
	usleep((philo->env->time_to_sleep)* 1000);
}
