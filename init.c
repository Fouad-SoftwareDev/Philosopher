/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:57:13 by fdahouk           #+#    #+#             */
/*   Updated: 2024/12/24 23:19:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philoshers(t_myenv *env, t_philo *philo, int pos)
{
	philo->eatcount = 0;
	philo->philo_id = pos + 1;
	philo->env = env;
	philo->last_meal_time = env->start_time;
	philo->forkone = pos;
	philo->forktwo = ((pos - 2 + env->philocount) % env->philocount) + 1;
	if (init_thread(philo) < 0)
		return (-5);
	return (0);
}

int	init_mutex(t_myenv *env)
{
	int	i;

	i = 0;
	while (i < env->philocount)
	{
		if (pthread_mutex_init(&env->forks[i], NULL) != 0)
			return (-3);
		i++;
	}
	if (pthread_mutex_init(&env->writingM, NULL) != 0)
		return (-4);
	return (0);
}

int	init_env(t_myenv *env)
{
	int	i;

	i = 0;
	env->philos = malloc(sizeof(t_philo) * (env->philocount));
	if (!env->philos)
		return (-1);
	env->forks = malloc(sizeof(pthread_mutex_t *) * env->philocount);
	if (!env->forks)
		return (-2);
	if (init_mutex(env) < 0)
		return (-1);
	while (i < env->philocount)
	{
		if (init_philosher(env, &env->philos[i], i) < 0)
			return (-1);
		i++;
	}
	return (0);
}

void	custom_print(char *msg, t_philo *philo, t_myenv *env)
{
	pthread_mutex_lock(&env->writingM);
	printf("%lu  %d  %s", (get_time_in_ms() - env->start_time), philo->philo_id, msg);
	pthread_mutex_unlock(&env->writingM);
}

int init_threads(t_philo *philo)
{
	if (pthread_create(philo->t_id, NULL, handler, NULL) != 0)
		return (-5);
	if (pthread_join(*philo->t_id, NULL) != 0)
		return (-6); 
	return (0);
}
