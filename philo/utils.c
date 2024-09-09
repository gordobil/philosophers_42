/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:41:44 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/09 12:15:06 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_logs(long long time, int philo, char log)
{
	if (log == 'f')
		printf("%lld %d has taken a fork\n", time, philo);
	else if (log == 'e')
		printf("%lld %d is eating\n", time, philo);
	else if (log == 's')
		printf("%lld %d is sleeping\n", time, philo);
	else if (log == 't')
		printf("%lld %d is thinking\n", time, philo);
	else if (log == 'd')
		printf("%lld %d died\n", time, philo);
	else
		return (-1);
	return (0);
}

long long	timer(long long past_time)
{
	struct timeval	s_time;
	long long		time;

	gettimeofday(&s_time, NULL);
	time = (s_time.tv_sec * 1000) + (s_time.tv_usec / 1000);
	if (past_time != NULL)
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
