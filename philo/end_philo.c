/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:37:57 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/18 13:40:12 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals(t_info *info, int ate)
{
	if (ate == info->philo_count && info->min_meals > -1)
	{
		info->all_ate = 1;
		print_logs(info->min_meals, 'a', info);
		return (1);
	}
	return (0);
}

int	check_death(t_info *info)
{
	int		i;
	int		ate;

	pthread_mutex_lock(&info->death);
	while (info->all_ate == 0 && info->died == 0)
	{
		i = -1;
		ate = 0;
		while (++i < info->philo_count && info->died != 1)
		{
			if (timer(info->philos[i].last_eat) >= info->time_to_die)
			{
				info->died = 1;
				print_logs(i + 1, 'd', info);
				return (pthread_mutex_unlock(&info->death), -1);
			}
			else if (info->philos[i].times_eaten >= info->min_meals)
				ate++;
		}
		if (check_meals(info, ate) != 0 || info->died != 0)
			return (pthread_mutex_unlock(&info->death), 1);
	}
	pthread_mutex_unlock(&info->death);
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
	pthread_mutex_destroy(&(info->eating));
	pthread_mutex_destroy(&(info->death));
}
