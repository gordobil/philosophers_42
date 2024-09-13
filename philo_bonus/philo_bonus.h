/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:10:56 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/13 13:56:54 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define CYAN	"\033[1;93m"
# define YELLOW	"\033[1;96m" 
# define RED	"\033[31m"
# define WHITE	"\033[0m"

struct	s_info;

typedef struct s_philo
{
	int					philo;
	int					l_fork;
	int					r_fork;
	int					times_eaten;
	long long			last_eat;
	pthread_t			thread;
	struct s_info		*info;
}						t_philo;

typedef struct s_info
{
	int					philo_count;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					min_eat;
	int					ate;
	int					died;
	long long			timer_start;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		printing;
}						t_info;

//MAIN
int			init(t_info *info, char **argv);
int			check_args(char **argv);
void		sleeping(long long time);
int			check_death(t_info *info);
void		exit_philo(t_info *info);

//UTILS
long long	timer(long long past_time);
int			print_logs(int philo, char log, t_info *info);
long		ft_atoi(const char *str);

#endif
