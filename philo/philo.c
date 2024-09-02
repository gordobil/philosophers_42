/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:10:17 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/02 14:07:56 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(t_args *args, char **argv)
{
	if (check_args(argv) != 0)
		return (-1);
	args->philos = atoi(argv[1]);
	args->time_to_die = atoi(argv[2]);
	args->time_to_eat = atoi(argv[3]);
	args->time_to_sleep = atoi(argv[4]);
	if (argv[5] == NULL)
		args->min_eat = -1;
	else
		args->min_eat = atoi(argv[5]);
	if (!args->philos || !args->time_to_die || !args->time_to_eat
		|| !args->time_to_sleep || !args->min_eat)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_args	args;

	if ((argc != 5 && argc != 6) || init_args(&args, argv) != 0)
	{
		printf ("Invalid arguments\n");
		return (-1);
	}
	printf("debug\n");
	return (0);
}
