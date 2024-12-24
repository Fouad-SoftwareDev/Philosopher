/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:35:31 by fdahouk           #+#    #+#             */
/*   Updated: 2024/12/24 23:13:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				philo_id;
	int				forkone;
	int				forktwo;
	int				eatcount;
	unsigned long	last_meal_time;
	struct s_env	*env;
	pthread_t		t_id;
}	t_philo;

typedef struct s_myenv
{
	int					philocount;
	int					max_timestoeat;
	int					time_to_sleep;
	int					time_to_eat;
	int					time_to_die;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		writing_m;
	unsigned long		start_time;
}	t_myenv;

int					ft_atoi(char *nptr);
int					check_arg_validity(char	**argv, int argc, t_myenv *myenv);
int					init_mutex(t_myenv *env);
int					init_philoshers(t_myenv *env, t_philo *philo, int pos);
int					init_env(t_myenv *env);
init				init_threads(t_philo *philo);
void				*handler(void *arg);
void				custom_print(char *msg, t_philo *philo, t_myenv *env);
unsigned long		get_time_in_ms(void);

#endif