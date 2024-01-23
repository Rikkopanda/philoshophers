/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread_helper_functions.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:34:17 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/23 12:37:16 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_if_die(t_philo	*philo, t_data *data)
{
	pthread_mutex_lock(&(*philo).data->die_lock);
	pthread_mutex_lock(&(*philo).data->time_since_meal);
	if ((*philo).time_since_meal > (*philo).data->time_to_die)
	{
		pthread_mutex_unlock(&(*philo).data->time_since_meal);
		(*data).died_bool = 1;
		pthread_mutex_unlock(&(*philo).data->die_lock);
		usleep(500);
		printfunc_monitor((philo), &((*data).monitor_tv), "died\n");
		return (1);
	}
	pthread_mutex_unlock(&(*philo).data->time_since_meal);
	pthread_mutex_unlock(&(*philo).data->die_lock);
	return (0);
}

int	check_if_done(t_philo *philo)
{
	pthread_mutex_lock(&(*philo).data->done_lock);
	if (philo->done_bool)
	{
		return (pthread_mutex_unlock(&(*philo).data->done_lock), 1);
	}
	pthread_mutex_unlock(&(*philo).data->done_lock);
	return (0);
}

int	printfunc_monitor(t_philo *philo, struct timeval *tv, char *print_str)
{
	int		current_time;

	gettimeofday(tv, NULL);
	current_time = ((*tv).tv_sec * 1000) + ((*tv).tv_usec / 1000)
		- philo->data->start_time;
	pthread_mutex_lock(&(*philo).data->print_lock);
	printf("%d %d %s", current_time, (*philo).philo_nbr, print_str);
	pthread_mutex_unlock(&(*philo).data->print_lock);
	return (0);
}
