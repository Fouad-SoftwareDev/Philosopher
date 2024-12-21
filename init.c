/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdahouk <fdahouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:57:13 by fdahouk           #+#    #+#             */
/*   Updated: 2024/12/20 15:24:02 by fdahouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philoshers(t_myenv *env)
{
	int	i;

	i = 1;
	while (i <env->philocount)
	{
		env->philos[i].philo_id = i;
		i++;
	}
}

void	init_forks(t_myenv *env)
{
	int	i;

	i = 1;
	while (i <env->philocount)
	{
		env->forks[i].fork_id = i;
		env->forks[i].available = 1;
		i++;
	}
}

void	init_env(t_myenv *env)
{
	env->forks = malloc(sizeof(t_forktoeat) * (env->philocount));
	env->philos = malloc(sizeof(t_philo) * (env->philocount));
}