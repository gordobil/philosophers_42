/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:37:57 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/10 13:43:34 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_info *info)
{
	int	i;
	int	ate;

	i = 0;
	ate = 0;
	while (info->ate == 0)
	{
		while (i < info->philo_count && info->died != 1)
		{
			if (timer(info->philos[i].last_eat) >= info->time_to_die)
			{
				print_logs(timer(-1), 0, 'd', info);
				info->died = 1;
				break ;
			}
			else if (info->philos[i].times_eaten >= info->min_eat)
				ate++;
			i++;
		}
		if (ate == info->philo_count)
		{
			print_logs(timer(-1), info->min_eat, 'a', info);
			info->ate = 1;
		}
	}
}

void	exit_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_count)
	{
		pthread_join(info->philos[i].thread, NULL);
		pthread_mutex_destroy(&(info->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(info->printing));
}
