/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:10:56 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/24 13:23:14 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define CYAN	"\033[1;93m"
# define RED	"\033[1;96m" 
# define GREEN	"\033[1;31m"
# define WHITE	"\033[0m"

struct	s_info;

typedef struct s_philo
{
	int					philo;
	int					times_eaten;
	long long			last_eat;
	struct s_info		*info;
	pid_t				process_id;
	pthread_t			death_thr;
}						t_philo;

typedef struct s_info
{
	int					philo_count;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					min_meals;
	int					died;
	long long			timer_start;
	t_philo				*philos;
	sem_t				*forks;
	sem_t				*printing;
	sem_t				*eating;
}						t_info;

//MAIN
int			init(t_info *info, char **argv);
int			check_args(char **argv);
void		sleeping(long long time);
void		*check_death(void *philo_void);
void		exit_philo(t_info *info, t_philo *philos);

//UTILS
long long	timer(long long past_time);
void		print_logs(int philo, char log, t_info *info);
long		ft_atoi(const char *str);

#endif
