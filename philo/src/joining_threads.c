/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joining_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:25:02 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/16 18:12:13 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_forks(t_fork *forks, t_data *data)
{
	int	i;

	i = 0;
	while (i < (*data).n_of_philos)
	{
		pthread_mutex_destroy(&forks[i].lock);
		i++;
	}
	free(forks);
	free((*data).philos_ptr);
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
	philos->data->end = 1;
	pthread_mutex_destroy(philos->data->die_lock);
	pthread_mutex_destroy(philos->data->done_lock);
	pthread_mutex_destroy(philos->data->time_since_meal);
	pthread_mutex_destroy(philos->data->print_lock);
	pthread_mutex_destroy(philos->data->start_time_lock);
	pthread_mutex_destroy(philos->data->cnt_to_start_th_lock);
	free(philos->data->die_lock);
	free(philos->data->done_lock);
	free(philos->data->time_since_meal);
	free(philos->data->print_lock);
	free(philos->data->cnt_to_start_th_lock);
	free(philos->data->start_time_lock);
	destroy_forks(philos->data->forks_ptr, philos->data);
}
