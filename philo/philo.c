/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:10:17 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/09 13:45:12 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo, t_info *info)
{
	int	i;
	int	ate;

	pthread_mutex_lock(&(info->forks[philo->l_fork]));
	print_logs(timer(NULL), philo->philo, 'f', info);
	pthread_mutex_lock(&(info->forks[philo->r_fork]));
	print_logs(timer(NULL), philo->philo, 'f', info);
	print_logs(timer(NULL), philo->philo, 'e', info);
	sleeping(info->time_to_eat, philo);
	philo->times_eaten++;
	philo->last_eat = timer(NULL);
	pthread_mutex_unlock(&(info->forks[philo->l_fork]));
	pthread_mutex_unlock(&(info->forks[philo->r_fork]));
	i = 0;
	ate = 0;
	while (i < info->philo_count && info->min_eat != -1)
	{
		if (info->philos[i].times_eaten >= info->min_eat)
			ate++;
		i++;
	}
	if (ate == info->philo_count)
		info->ate == 1;
}

void	thread_actions(void *philo_void)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)philo_void;
	info = philo->info;
	if (philo->philo % 2 != 0)
		usleep(6000);
	while (info->died == 0)
	{
		eating(philo, info);
		if (info->min_eat > -1 && info->ate == 1)
		{
			exit_philo(info);
			return ;
		}
		print_logs(timer(NULL), philo->philo, 's', info);
		sleeping(timer(NULL), philo);
		print_logs(timer(NULL), philo->philo, 't', info);
	}
	if (info->died != 0)
		exit_philo(info);
}

int	philo(t_info *info)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = info->philos;
	info->timer_start = timer(NULL);
	while (i < info->philo_count)
	{
		pthread_create(&philo[i].thread, NULL, thread_actions, &philo[i]);
		philo[i].last_eat = timer(NULL);
		i++;
	}
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
