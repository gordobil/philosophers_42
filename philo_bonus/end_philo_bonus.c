/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_philo_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:37:57 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/25 12:35:05 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *philo_void)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)philo_void;
	info = philo->info;
	while (1)
	{
		sem_wait(info->eating);
		if (timer(philo->last_eat) >= info->time_to_die)
		{
			info->died = 1;
			print_logs(philo->philo, 'd', info);
			sem_wait(info->printing);
			exit (1);
		}
		sem_post(info->eating);
		if ((philo->times_eaten >= info->min_meals && info->min_meals > -1)
			|| info->died != 0)
			break ;
	}
	return (NULL);
}

void	close_semaphores(t_info *info)
{
	sem_close(info->forks);
	sem_close(info->printing);
	sem_close(info->eating);
	sem_unlink("forks");
	sem_unlink("eating");
	sem_unlink("printing");
}

void	exit_philo(t_info *info, t_philo *philos)
{
	int	i;
	int	wait_ret;
	int	ate;

	i = -1;
	wait_ret = 0;
	ate = 0;
	while (++i < info->philo_count)
	{
		waitpid(-1, &wait_ret, 0);
		if (wait_ret != 0)
		{
			i = -1;
			while (++i < info->philo_count)
				kill(philos[i].process_id, 15);
			break ;
		}
		else
			ate++;
	}
	if (ate == info->philo_count)
		print_logs(ate, 'a', info);
	close_semaphores(info);
}
