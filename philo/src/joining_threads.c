/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joining_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:25:02 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/23 12:17:08 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_forks(t_data *data)
{
	int				i;
	pthread_mutex_t	*fork;

	fork = data->forks;
	i = 0;
	while (i < (*data).n_of_philos)
	{
		pthread_mutex_destroy(fork);
		i++;
		fork += 1;
	}
	free(data->forks);
	free((*data).philos_ptr);
}

void	destroy_locks(t_data *data)
{
	pthread_mutex_destroy(&data->die_lock);
	pthread_mutex_destroy(&data->done_lock);
	pthread_mutex_destroy(&data->time_since_meal);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->start_signal);
	pthread_mutex_destroy(&data->start_time_lock);
	pthread_mutex_destroy(&data->cnt_to_start_th_lock);
	destroy_forks(data);
}

void	join_philos(t_philo *philos, int n_of_philos)
{
	int	i;

	i = 0;
	pthread_join(philos->data->monitor_th_id, NULL);
	i = 0;
	while (i < n_of_philos)
	{
		pthread_join(philos[i].th_id, NULL);
		i++;
	}
	destroy_locks(philos->data);
}
