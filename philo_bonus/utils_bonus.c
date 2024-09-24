/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:41:44 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/24 11:56:30 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_logs(int philo, char log, t_info *info)
{
	sem_wait(info->printing);
	if (info->died == 0 && info->all_ate == 0 && log != 'a' && log != 'd')
	{
		printf(CYAN"%lld "WHITE, timer(info->timer_start));
		if (log == 'f')
			printf("%d has taken a fork\n", philo);
		else if (log == 'e')
			printf("%d is eating\n", philo);
		else if (log == 's')
			printf("%d is sleeping\n", philo);
		else if (log == 't')
			printf("%d is thinking\n", philo);
	}
	else if (log == 'a' || log == 'd')
	{
		printf(CYAN"%lld "WHITE, timer(info->timer_start));
		if (log == 'a')
			printf(GREEN"All ate at least %d time(s)\n"WHITE, info->min_meals);
		else if (log == 'd')
			printf("%d "RED"died\n"WHITE, philo);
	}
	sem_post(info->printing);
}

long long	timer(long long past_time)
{
	struct timeval	s_time;
	long long		time;

	gettimeofday(&s_time, NULL);
	time = (s_time.tv_sec * 1000) + (s_time.tv_usec / 1000);
	if (past_time > -1)
		return (time - past_time);
	return (time);
}

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] > '9' || argv[i][j] < '0')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

long	ft_atoi(const char *str)
{
	long	result;
	long	sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}
