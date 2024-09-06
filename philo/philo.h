/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:10:56 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/06 13:53:13 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

struct s_info;

typedef struct s_philo
{
	int					philo;
	int					l_fork;
	int					r_fork;
	long long			last_eat;
	pthread_t			thread;
	struct s_info		*info;
}						t_philo;

typedef struct s_info
{
	int					philo_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					min_eat;
	int					died;
	long long			timer_start;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		printing;
}						t_info;

int			init(t_info *info, char **argv);
int			check_args(char **argv);
long long	timer(t_info *info);
long		ft_atoi(const char *str);

#endif
