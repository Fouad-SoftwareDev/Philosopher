/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:35:31 by fdahouk           #+#    #+#             */
/*   Updated: 2025/01/06 02:03:43 by marvin           ###   ########.fr       */
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
	struct s_myenv	*env;
	pthread_t		t_id;
}	t_philo;

typedef struct s_myenv
{
	int					philocount;
	int					max_timestoeat;
	int					time_to_sleep;
	int					time_to_eat;
	int					time_to_die;
	int					stop_death;
	int					stop_eating;
	t_philo				*ph;
	pthread_mutex_t		*forks;
	pthread_mutex_t		writing_m;
	pthread_mutex_t		meal_m;
	pthread_mutex_t		death_m;
	unsigned long		start_time;
}	t_myenv;

int					ft_atoi(char *nptr);
int					check_arg_validity(char	**argv, int argc, t_myenv *myenv);
int					init_mutex(t_myenv *env);
int					init_env(t_myenv *env);
int					init_threadsallthreads(t_myenv *env);
int					check_philosopher(t_philo *ph);
int					check_eatcount(t_myenv *env);
int					someone_died(t_philo *ph);
int					onlynumber(char *s);
void				*handler(void *arg);
void				*handler1(void *arg);
void				monitor_death(t_myenv *env);
void				init_philoshers(t_myenv *env, t_philo *philo, int pos);
void				custom_print(char *msg, t_philo *philo);
void				clean_memory(t_myenv *env);
void				destroy_mutex(t_myenv *env);
void				eat(t_philo *philo);
void				sleeping(t_philo *philo);
void				thinking(t_philo *ph);
void				take_forks(t_philo *philo);
void				join_all_thread(t_myenv *env);
unsigned long		get_time_in_ms(void);

#endif