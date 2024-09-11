/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:10:17 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/11 20:40:19 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(long long time)
{
	long long	start;

	start = timer(-1);
	while (timer(start) <= time)
		usleep(50);
}

void	eating(t_philo *philo, t_info *info)
{
	int	i;
	int	ate;

	pthread_mutex_lock(&(info->forks[philo->l_fork]));
	print_logs(philo->philo, 'f', info);
	pthread_mutex_lock(&(info->forks[philo->r_fork]));
	print_logs(philo->philo, 'f', info);
	print_logs(philo->philo, 'e', info);
	sleeping(info->time_to_eat);
	philo->times_eaten++;
	philo->last_eat = timer(-1);
	pthread_mutex_unlock(&(info->forks[philo->l_fork]));
	pthread_mutex_unlock(&(info->forks[philo->r_fork]));
	
}

void	*thread_actions(void *philo_void)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)philo_void;
	info = philo->info;
	if (philo->philo % 2 == 0)
		usleep(500);
	while (info->died == 0 && info->ate == 0)
	{
		eating(philo, info);
		if (info->died != 0 || (info->min_eat > -1 && info->ate != 0))
			break ;
		print_logs(philo->philo, 's', info);
		sleeping(info->time_to_sleep);
		if (info->died != 0 || (info->min_eat > -1 && info->ate != 0))
			break ;
		print_logs(philo->philo, 't', info);
	}
}

int	philo(t_info *info)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = info->philos;
	info->timer_start = timer(-1);
	while (i < info->philo_count)
	{
		pthread_create(&philo[i].thread, NULL, thread_actions, &philo[i]);
		philo[i].last_eat = timer(-1);
		i++;
	}
	check_death(info);
	exit_philo(info);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if ((argc != 5 && argc != 6) || init(&info, argv) != 0)
	{
		printf ("Error initializing\n");
		return (-1);
	}
	if (philo(&info) != 0)
	{
		printf ("Error\n");
		return (-1);
	}
	return (0);
}
