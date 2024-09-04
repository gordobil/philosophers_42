/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:44:59 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/04 13:47:21 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_info *info)
{
	int	i;

	info->forks = malloc(info->philo_count * sizeof(pthread_mutex_t));
	if (!info->forks)
		return (-1);
	i = info->philo_count;
	while (--i >= 0)
		pthread_mutex_init(&info->forks[i], NULL);
	pthread_mutex_init(&info->printing, NULL);
	return (0);
}

int	init_philos(t_info *info)
{
	int	i;

	info->philos = malloc(info->philo_count * sizeof(t_philo));
	if (!info->philos)
		return (-1);
	i = info->philo_count;
	while (i > 0)
	{
		info->philos[i - 1].info = info;
		info->philos[i - 1].philo = i;
		info->philos[i - 1].l_fork = i;
		info->philos[i - 1].r_fork = i + 1;
		if (i == info->philo_count)
			info->philos[i - 1].r_fork = 1;
		i--;
	}
	return (0);
}

int	init(t_info *info, char **argv)
{
	if (check_args(argv) != 0)
		return (-1);
	info->philo_count = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] == NULL)
		info->min_eat = -1;
	else
		info->min_eat = ft_atoi(argv[5]);
	if (info->philo_count < 1 || info->time_to_die < 0 || info->time_to_eat < 0
		|| info->time_to_sleep < 0 || info->min_eat < -1)
		return (-1);
	if (init_philos(info) != 0 || init_mutex(info) != 0)
		return (-1);
	return (0);
}
