/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_philo_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:37:57 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/18 14:26:33 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	check_death(t_info *info)
{
	int		i;
	int		ate;

	sem_wait(info->death);
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
				break ;
			}
			else if (info->philos[i].times_eaten >= info->min_meals)
				ate++;
		}
		if (check_meals(info, ate) != 0 || info->died != 0)
			break ;
	}
	sem_post(info->death);
	exit_philo(info);
}

void	exit_philo(t_info *info)
{
	int	i;

	i = -1;
	waitpid(-1, NULL, 0);
	sem_close(info->forks);
	sem_close(info->printing);
	sem_close(info->eating);
	sem_close(info->death);
	sem_unlink("forks");
	sem_unlink("eating");
	sem_unlink("printing");
	sem_unlink("death");
}
