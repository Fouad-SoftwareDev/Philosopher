/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdahouk <fdahouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:21:14 by fdahouk           #+#    #+#             */
/*   Updated: 2024/12/20 16:08:15 by fdahouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char	**argv)
{
	t_myenv	*myenv;

	myenv = malloc(sizeof(t_myenv));
	myenv->start_time = get_time_in_ms();
	if (argc < 5 || argc > 6)
		printf("number of argument should be 4 or 5");
	else
	{
		if (check_arg_validity(argv ,argc, myenv) !=0)
			printf("include only postive number between 1 and 2147483647");
		else 
		{
			
		}
	}
	free(myenv);
	return (0);
}

// void	case4a(char	**argv)
// {
// 	if (ft_atoi(argv[0]) == 1)
// 	{
// 		do_something();
// 		initilase 1 philo and 1 thread he will just sleep and die can't eat nor think
// 	}
// 	else
// 	{
// 		// initialse more than 1 philo and code the rest
// 	}
// }

// argument check no negative numbers allowed
int	check_arg_validity(char	**argv,int argc, t_myenv *myenv)
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
