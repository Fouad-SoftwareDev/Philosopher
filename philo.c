/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:21:14 by fdahouk           #+#    #+#             */
/*   Updated: 2024/12/24 23:11:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char	**argv)
{
	t_myenv	myenv;

	myenv.start_time = get_time_in_ms();
	if (argc < 5 || argc > 6)
		printf("number of argument should be 4 or 5");
	else
	{
		if (check_arg_validity(argv, argc, &myenv) != 0)
			printf("include only postive number between 1 and 2147483647");
		else
		{
		}
	}
	return (0);
}
