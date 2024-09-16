/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:10:17 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/16 12:38:11 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sleeping(long long time)
{
	long long	start;

	start = timer(-1);
	while (timer(start) <= time)
		usleep(50);
}

void	eating(t_philo *philo, t_info *info)
{
	sem_wait(info->forks);
	print_logs(philo->philo, 'f', info);
	sem_wait(info->forks);
	print_logs(philo->philo, 'f', info);
	philo->last_eat = timer(-1);
	print_logs(philo->philo, 'e', info);
	sleeping(info->time_to_eat);
	philo->times_eaten++;
	sem_post(info->forks);
	sem_post(info->forks);
}

void	fork_process(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	if (philo->philo % 2 == 0)
		usleep(50000);
	pthread_create(philo->death, NULL, check_death, philo);
	while (info->died == 0 && info->ate == 0)
	{
		if (info->philo_count > 1)
			eating(philo, info);
		else
			break ;
		if (info->died != 0 || (info->min_eat > -1 && info->ate != 0))
			break ;
		print_logs(philo->philo, 's', info);
		sleeping(info->time_to_sleep);
		if (info->died != 0 || (info->min_eat > -1 && info->ate != 0))
			break ;
		print_logs(philo->philo, 't', info);
	}
	pthread_join(philo->death, NULL);
}

void	philo(t_info *info)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = info->philos;
	info->timer_start = timer(-1);
	while (i < info->philo_count)
	{
		philo->process_id = fork();
		if (philo->process_id == 0)
			fork_process(philo);
		else if (philo->process_id < 0)
			return (-1);
	}
	exit_philo(info);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if ((argc != 5 && argc != 6) || init(&info, argv) != 0)
	{
		printf ("Error initializing\n");
		return (-1);
	}
	philo(&info);
	return (0);
}
