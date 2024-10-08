/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:10:17 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/25 12:44:49 by ngordobi         ###   ########.fr       */
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

void	eat(t_philo *philo, t_info *info)
{
	sem_wait(info->forks);
	print_logs(philo->philo, 'f', info);
	sem_wait(info->forks);
	print_logs(philo->philo, 'f', info);
	sem_wait(info->eating);
	print_logs(philo->philo, 'e', info);
	philo->last_eat = timer(-1);
	sem_post(info->eating);
	sleeping(info->time_to_eat);
	philo->times_eaten++;
	sem_post(info->forks);
	sem_post(info->forks);
}

void	fork_process(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	philo->last_eat = timer(-1);
	pthread_create(&(philo->death_thr), NULL, check_death, philo);
	if (philo->philo % 2 == 0)
		usleep(50000);
	while (info->died == 0)
	{
		eat(philo, info);
		if (info->min_meals > -1 && philo->times_eaten >= info->min_meals)
			break ;
		print_logs(philo->philo, 's', info);
		sleeping(info->time_to_sleep);
		print_logs(philo->philo, 't', info);
	}
	pthread_join(philo->death_thr, NULL);
	exit (0);
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
		philo[i].process_id = fork();
		if (philo[i].process_id == 0)
			fork_process(&philo[i]);
		else if (philo[i].process_id < 0)
			break ;
		i++;
	}
	exit_philo(info, philo);
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
