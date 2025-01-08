/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:21:14 by fdahouk           #+#    #+#             */
/*   Updated: 2025/01/07 22:30:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char	**argv)
{
	t_myenv	myenv;

	myenv.start_time = get_time_in_ms();
	if (argc < 5 || argc > 6)
		printf("number of argument should be 4 or 5 \n");
	else
	{
		if (check_arg_validity(argv, argc, &myenv) != 0)
		{
			printf("include only postive number between 1 and 2147483647\n");
			return (1);
		}
		else
		{
			if (init_env(&myenv) < 0)
			{
				printf("An error occured during initialisation");
			}
			monitor_death(&myenv);
			join_all_thread(&myenv);
			if (myenv.stop_eating)
				printf("\033[1;32mNo Philospher Died!!\033[0m\n");
		}
	}
	return (0);
}
