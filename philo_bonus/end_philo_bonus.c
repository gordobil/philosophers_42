/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_philo_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:37:57 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/20 12:39:49 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_meals(t_info *info)
{
	int		ate;
	int		i;
	t_philo	*philo;

	ate = 0;
	i = 0;
	philo = info->philos;
	while (i < info->philo_count)
	{
		if (philo[i].times_eaten >= info->min_meals)
			ate++;
		i++;
	}
	if (ate == info->philo_count && info->min_meals > -1)
	{
		info->all_ate = 1;
		print_logs(info->min_meals, 'a', info);
		return (1);
	}
	return (0);
}

void	*check_death(void *philo_void)
{
	t_philo	*philo;
	t_info	*info;

	philo = (void *)philo_void;
	info = philo->info;
	while (info->all_ate == 0 && info->died == 0)
	{
		sem_wait(info->eating);
		if (timer(philo->last_eat) >= info->time_to_die)
		{
			info->died = 1;
			print_logs(philo->philo, 'd', info);
			sem_post(info->eating);
			break ;
		}
		if (check_meals(info) != 0 || info->died != 0)
		{
			sem_post(info->eating);
			break ;
		}
		sem_post(info->eating);
	}
}

void	exit_philo(t_info *info)
{
	int	i;

	i = -1;
	waitpid(-1, NULL, 0);
	sem_close(info->forks);
	sem_close(info->printing);
	sem_close(info->eating);
	sem_unlink("forks");
	sem_unlink("eating");
	sem_unlink("printing");
}
