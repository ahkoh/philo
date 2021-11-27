/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 23:35:36 by skoh              #+#    #+#             */
/*   Updated: 2021/11/27 18:20:57 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

static bool	init_var(t_app *app, char **argv)
{
	app->status = WAIT;
	app->min_eat = INT_MAX;
	if (ft_atoi_try(*argv++, &app->philo_count)
		&& ft_atoi_try(*argv++, &app->time_die_ms)
		&& ft_atoi_try(*argv++, &app->time_eat_ms)
		&& ft_atoi_try(*argv++, &app->time_sleep_ms))
		return (*argv == NULL || ft_atoi_try(*argv, &app->min_eat));
	return (false);
}

static void	*philo_work(t_philo	*st)
{
	while (st->app->status == WAIT)
		usleep(10);
	st->last_eat = now();
	usleep((st->id - 1) % 2 * 500);
	while (st->app->status == RUN)
	{
		msg(st->print, st->app->start, MSG_THINK, st->id);
		if (!pthread_mutex_lock(st->forks[1]) && st->app->status == RUN)
			msg(st->print, st->app->start, MSG_FORK, st->id);
		if (!pthread_mutex_lock(st->forks[0]) && st->app->status == RUN)
		{
			msg(st->print, st->app->start, MSG_FORK, st->id);
			st->last_eat = msg(st->print, st->app->start, MSG_EAT,
					st->id) + st->app->start;
			st->eat_count++;
			msleep(st->app->time_eat_ms);
		}
		pthread_mutex_unlock(st->forks[0]);
		pthread_mutex_unlock(st->forks[1]);
		if (st->app->status != RUN)
			break ;
		msg(&st->app->print, st->app->start, MSG_SLEEP, st->id);
		msleep(st->app->time_sleep_ms);
	}
	return (pthread_mutex_destroy(&st->fork), NULL);
}

static void	create_philos(t_app *app, int n)
{
	t_philo		*arg;

	if (n > 1)
		create_philos(app, n - 1);
	arg = app->philos + n - 1;
	arg->id = n;
	arg->app = app;
	arg->print = &app->print;
	arg->eat_count = 0;
	arg->last_eat = 0;
	pthread_mutex_init(&arg->fork, NULL);
	arg->forks[0] = &arg->fork;
	app->philos[n % app->philo_count].forks[1] = &arg->fork;
	pthread_create(&arg->thread, NULL, (void *(*)(void *))philo_work, arg);
	pthread_detach(arg->thread);
}

static void	run_and_wait(t_app *app)
{
	int	i;
	int	min_eat_count;

	app->start = now();
	app->status = RUN;
	usleep(999);
	min_eat_count = 0;
	i = -1;
	while (app->status == RUN && min_eat_count < app->philo_count)
	{
		if (++i == app->philo_count)
		{
			i = (min_eat_count = 0);
			usleep(333);
		}
		if (app->philos[i].last_eat
			&& app->philos[i].last_eat + app->time_die_ms < now())
		{
			app->status = STOP;
			pthread_mutex_lock(&app->print);
			printf(MSG_DIE, now() - app->start, app->philos[i].id);
		}
		min_eat_count += app->philos[i].eat_count >= app->min_eat;
	}
	app->status = STOP;
}

int	main(int argc, char **argv)
{
	t_app	app;

	if (argc < 5 || argc > 6 || !init_var(&app, argv + 1))
		return (!!printf("Error: wrong argument(s).\n"));
	app.philos = (t_philo *)malloc(sizeof(t_philo) * app.philo_count);
	if (!app.philos)
		return (!!printf("Error: malloc failed.\n"));
	pthread_mutex_init(&app.print, NULL);
	create_philos(&app, app.philo_count);
	run_and_wait(&app);
	pthread_mutex_destroy(&app.print);
	free(app.philos);
	return (EXIT_SUCCESS);
}
