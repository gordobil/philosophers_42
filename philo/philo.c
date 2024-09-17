/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:10:17 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/17 12:55:56 by ngordobi         ###   ########.fr       */
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

void	eat(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&(info->forks[philo->l_fork - 1]));
	print_logs(philo->philo, 'f', info);
	pthread_mutex_lock(&(info->forks[philo->r_fork - 1]));
	print_logs(philo->philo, 'f', info);
	pthread_mutex_lock(&(info->eating));
	print_logs(philo->philo, 'e', info);
	philo->last_eat = timer(-1);
	pthread_mutex_unlock(&(info->eating));
	sleeping(info->time_to_eat);
	philo->times_eaten++;
	pthread_mutex_unlock(&(info->forks[philo->l_fork - 1]));
	pthread_mutex_unlock(&(info->forks[philo->r_fork - 1]));
}

void	*thread_actions(void *philo_void)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)philo_void;
	info = philo->info;
	if (philo->philo % 2 == 0)
		usleep(50000);
	while (info->died == 0 && info->ate == 0)
	{
		if (info->philo_count > 1)
			eat(philo, info);
		else
			break ;
		if (info->died != 0 || (info->min_meals > -1 && info->ate != 0))
			break ;
		print_logs(philo->philo, 's', info);
		sleeping(info->time_to_sleep);
		if (info->died != 0 || (info->min_meals > -1 && info->ate != 0))
			break ;
		print_logs(philo->philo, 't', info);
	}
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
		pthread_create(&philo[i].thread, NULL, thread_actions, &philo[i]);
		if (!philo[i].thread)
		{
			printf("Error creating threads\n");
			exit_philo(info);
			return ;
		}
		pthread_join(info->philos[i].thread, NULL);
		philo[i].last_eat = timer(-1);
		i++;
	}
	check_death(info);
	exit_philo(info);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if ((argc != 5 && argc != 6) || init(&info, argv) != 0)
	{
		printf("Error initializing\n");
		return (-1);
	}
	philo(&info);
	return (0);
}
