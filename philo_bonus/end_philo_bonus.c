/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_philo_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:37:57 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/16 13:59:40 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_death(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	while (1)
	{
		if (timer(philo->last_eat) >= info->time_to_die)
		{
			info->died = 1;
			sem_wait("printing");
			print_logs(philo->philo, 'd', info);
			return (-1);
		}
		if (philo->times_eaten >= info->min_eat && info->min_eat > -1)
		{
			info->ate = 1;
			print_logs(info->min_eat, 'a', info);
			return (1);
		}
	}
	return (0);
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
