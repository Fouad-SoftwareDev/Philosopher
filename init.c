/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:57:13 by fdahouk           #+#    #+#             */
/*   Updated: 2025/01/08 00:02:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philoshers(t_myenv *env, t_philo *philo, int pos)
{
	philo->eatcount = 0;
	philo->philo_id = pos + 1;
	philo->env = env;
	philo->last_meal_time = env->start_time;
	philo->forkone = pos;
	philo->forktwo = (pos - 1 + env->philocount) % env->philocount;
}

int	init_mutex(t_myenv *env)
{
	int	i;

	i = 0;
	while (i < env->philocount)
	{
		if (pthread_mutex_init(&env->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&env->forks[i]);
			return (-3);
		}
		i++;
	}
	if (pthread_mutex_init(&env->writing_m, NULL) != 0
		|| pthread_mutex_init(&env->death_m, NULL) != 0
		|| pthread_mutex_init(&env->meal_m, NULL) != 0)
	{
		while (--i >= 0)
			pthread_mutex_destroy(&env->forks[i]);
		return (-4);
	}
	return (0);
}

int	init_env(t_myenv *env)
{
	int	i;

	i = 0;
	env->stop_death = 0;
	env->stop_eating = 0;
	env->ph = malloc(sizeof(t_philo) * (env->philocount));
	if (!env->ph)
		return (-1);
	env->forks = malloc(sizeof(pthread_mutex_t) * env->philocount);
	if (!env->forks)
		return (-2);
	if (init_mutex(env) < 0)
		return (-1);
	while (i < env->philocount)
	{
		init_philoshers(env, &env->ph[i], i);
		i++;
	}
	if (init_threadsallthreads(env) < 0)
		return (-1);
	return (0);
}

void	custom_print(char *msg, t_philo *ph)
{
	unsigned long	time;

	if (someone_died(ph))
			return ;
	if (!ph->env->stop_death)
	{	
		pthread_mutex_lock(&ph->env->writing_m);
		time = (get_time_in_ms() - ph->env->start_time);
		printf("%lu  %d%s\n", time, ph->philo_id, msg);
		pthread_mutex_unlock(&ph->env->writing_m);
	}
}
int	init_threadsallthreads(t_myenv *e)
{
	int	i;

	i = 0;
	while (i < e->philocount)
	{
		if (e->philocount == 1)
		{
			if (pthread_create(&e->ph[i].t_id, NULL, handler1, &e->ph[i]) != 0)
				return (-1);
		}
		else
		{
			if (pthread_create(&e->ph[i].t_id, NULL, handler, &e->ph[i]) != 0)
				return (-1);
		}
		i++;
	}
	return (0);
}
