/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:10:17 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/06 14:58:29 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo, t_info *info)
{
	
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
	}
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
		pthread_create(&philo[i]->thread, NULL, thread_actions, &philo[i]);
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
