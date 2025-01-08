/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:07:07 by fdahouk           #+#    #+#             */
/*   Updated: 2025/01/07 22:28:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eatcount(t_myenv *env)
{
	int	i;
	int	eat_stop;

	i = 0;
	eat_stop = 1;
	if (env->max_timestoeat < 0)
		return (0);
	while (i < env->philocount)
	{
		pthread_mutex_lock(&env->meal_m);
		if (env->ph[i].eatcount < env->max_timestoeat)
			eat_stop = 0;
		pthread_mutex_unlock(&env->meal_m);
		i++;
	}
	if (eat_stop)
	{
		pthread_mutex_lock(&env->death_m);
		env->stop_eating = 1;
		pthread_mutex_unlock(&env->death_m);
		return (1);
	}
	return (0);
}

int	someone_died(t_philo *ph)
{
	pthread_mutex_lock(&ph->env->death_m);
	if (ph->env->stop_death || ph->env->stop_eating)
	{
		pthread_mutex_unlock(&ph->env->death_m);
		return (1);
	}
	pthread_mutex_unlock(&ph->env->death_m);
	return (0);
}

void	thinking(t_philo *ph)
{
	custom_print(" is thinking", ph);
}

void	join_all_thread(t_myenv *env)
{
	int	i;

	i = 0;
	while (i < env->philocount)
	{
		pthread_join(env->ph[i].t_id, NULL);
		i++;
	}
	clean_memory(env);
}

void	sleeping(t_philo *philo)
{
	custom_print(" is sleeping", philo);
	usleep((philo->env->time_to_sleep) * 1000);
}
