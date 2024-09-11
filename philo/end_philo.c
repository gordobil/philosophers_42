/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:37:57 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/11 20:41:10 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_info *info)
{
	int	i;
	int	ate;

	while (info->ate == 0 && info->died == 0)
	{
		i = -1;
		ate = 0;
		while (++i < info->philo_count && info->died != 1)
		{
			if (timer(info->philos[i].last_eat) >= info->time_to_die)
			{
				info->died = 1;
				print_logs(i + 1, 'd', info);
				return (-1);
			}
			else if (info->philos[i].times_eaten >= info->min_eat)
				ate++;
		}
		if (ate == info->philo_count && info->min_eat > -1)
		{
			info->ate = 1;
			print_logs(info->min_eat, 'a', info);
			return (1);
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
