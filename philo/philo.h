/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 23:02:02 by skoh              #+#    #+#             */
/*   Updated: 2021/11/27 16:49:52 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# define MSG_THINK "%ld %d is thinking\n"
# define MSG_FORK "%ld %d has taken a fork\n"
# define MSG_EAT "%ld %d is eating\n"
# define MSG_SLEEP "%ld %d is sleeping\n"
# define MSG_DIE "%ld %d died\n"

enum e_app_status
{
	WAIT,
	RUN,
	STOP,
};

typedef struct s_philo	t_philo;

typedef struct s_app
{
	int					philo_count;
	int					time_die_ms;
	int					time_eat_ms;
	int					time_sleep_ms;
	int					min_eat;
	long				start;
	pthread_mutex_t		print;
	t_philo				*philos;
	enum e_app_status	status;
}						t_app;

struct s_philo
{
	pthread_t			thread;
	pthread_mutex_t		fork;
	pthread_mutex_t		*forks[2];
	t_app				*app;
	pthread_mutex_t		*print;
	int					id;
	long				last_eat;
	int					eat_count;
};

int		ft_atoi_try(const char *str, int *out);
long	now(void);
long	msg(pthread_mutex_t *mutex, long offset, char *s, int id);
void	msleep(int msec);

#endif