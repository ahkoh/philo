/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 23:01:33 by skoh              #+#    #+#             */
/*   Updated: 2021/11/27 18:34:29 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include "philo.h"

long	now(void)
{
	struct timeval	tv;
	struct timezone	tz;

	gettimeofday(&tv, &tz);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	msleep(int msec)
{
	const long	exp = now() + msec;

	while (now() < exp)
		usleep(333);
}

long	msg(pthread_mutex_t *mutex, long offset, char *s, int id)
{
	long	ms;

	if (pthread_mutex_lock(mutex))
		return (now() - offset);
	ms = now() - offset;
	printf(s, ms, id);
	pthread_mutex_unlock(mutex);
	return (ms);
}
