/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:44:59 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/16 11:52:43 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphores(t_info *info)
{
	sem_unlink("forks");
	sem_unlink("printing");
	info->forks = sem_open("forks", O_CREAT, S_IRWXU, info->philo_count);
	info->printing = sem_open("printing", O_CREAT, S_IRWXU, 1);
	if (!info->forks || !info->printing)
		return (-1);
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
		info->philos[i - 1].times_eaten = 0;
		info->philos[i - 1].last_eat = 0;
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
	info->died = 0;
	info->ate = 0;
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
