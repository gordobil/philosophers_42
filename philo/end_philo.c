/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:37:57 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/17 14:50:09 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals(t_info *info, int ate)
{
	if (ate == info->philo_count && info->min_meals > -1)
	{
		info->ate = 1;
		print_logs(info->min_meals, 'a', info);
		return (1);
	}
	return (0);
}

void	*check_death(void *info_void)
{
	t_info	*info;
	int		i;
	int		ate;

	info = (t_info *)info_void;
	while (info->ate == 0 && info->died == 0)
	{
		i = -1;
		ate = 0;
		while (++i < info->philo_count && info->died != 1)
		{
			printf ("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
			if (timer(info->philos[i].last_eat) >= info->time_to_die)
			{
				info->died = 1;
				print_logs(i + 1, 'd', info);
				break ;
			}
			else if (info->philos[i].times_eaten >= info->min_meals)
				ate++;
		}
		if (check_meals(info, ate) != 0 || info->died != 0)
			break ;
	}
	return (info_void);
}

void	exit_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_count)
	{
		pthread_mutex_destroy(&(info->forks[i]));
		i++;
	}
	// if (info->philos)
	// 	free(info->philos);
	// if (info->forks)
	// 	free(info->forks);
	pthread_mutex_destroy(&(info->printing));
	pthread_mutex_destroy(&(info->eating));
	// if (info)
	// 	free (info);
}
