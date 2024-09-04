/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:10:17 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/03 21:13:20 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(t_info *info, char **argv)
{
	if (check_info(argv) != 0)
		return (-1);
	info->philos = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] == NULL)
		info->min_eat = -1;
	else
		info->min_eat = ft_atoi(argv[5]);
	if (!info->philos || !info->time_to_die || !info->time_to_eat
		|| !info->time_to_sleep || !info->min_eat)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if ((argc != 5 && argc != 6) || init_args(&info, argv) != 0)
	{
		printf ("Invalid arguments\n");
		return (-1);
	}
	printf("debug\n");
	return (0);
}
