/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:33:37 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/23 14:16:41 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_start_time(t_data *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	(*data).start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void	init_last_meal_per_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_of_philos)
	{
		data->philos_ptr[i].last_meal_ms = data->start_time;
		i++;
	}
}
#include <errno.h>

void	thread_err_clean_up(t_data *data, int i)
{
	pthread_mutex_lock(&data->die_lock);
	data->died_bool = 1;
	pthread_mutex_unlock(&data->die_lock);
	while (i >= 0)
	{
		pthread_mutex_lock(&data->done_lock);
		data->philos_ptr[i - 1].done_bool = 1;
		pthread_mutex_unlock(&data->done_lock);
		pthread_join(data->philos_ptr[i - 1].th_id, NULL);
		i--;
	}
	pthread_join(data->monitor_th_id, NULL);
	destroy_locks(data);
	return ;
}

int	create_philos(t_philo **philos, t_data *data)
{
	int	i;

	init_data(philos, data);
	init_locks(data);
	pthread_create(&(*data).monitor_th_id, NULL, monitoring, data);
	if (!philos)
		return (-1);
	i = 1;
	pthread_mutex_lock(&data->start_signal);
	while (i <= (*data).n_of_philos)
	{
		if (pthread_create(&(*philos)[i - 1].th_id,
			NULL, routine, &(*philos)[i - 1]) != 0)
			return (thread_err_clean_up(data, i), -1);
		i++;
	}
	init_start_time(data);
	init_last_meal_per_philo(data);
	pthread_mutex_unlock(&data->start_signal);
	return (1);
}
