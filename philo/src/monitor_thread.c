/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:34:17 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/23 14:20:22 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_loop(t_data *data, int *i, int *done_count)
{
	t_philo	*cur_philo;
	struct timeval	tv;

	cur_philo = (*data).philos_ptr;
	while (*i < (*data).n_of_philos)
	{
		assign_time_since_last_meal(cur_philo, &tv);
		if (check_if_die(&cur_philo[*i], data))
			return (-1);
		if (check_if_done(&cur_philo[*i]))
			(*done_count)++;
		(*i)++;
	}
	return (1);
}

/*
	checking if it has eaten enough,
	or if it has died.
	Sets done_bool or died_bool.

	-----------
	Maybe for each thread??
*/
void	*monitoring(void *ptr)
{
	int				i;
	int				done_count;
	t_data			*data;

	data = (t_data *)ptr;
	if (data->n_of_philos == 1)
		return ((void *)ONLY_ONE_PHILO);
	pthread_mutex_lock(&data->start_signal);
	pthread_mutex_unlock(&data->start_signal);
	while (1)
	{
		done_count = 0;
		i = 0;
		if (check_loop(data, &i, &done_count) == -1)
			return (NULL);
		if (done_count == (*data).n_of_philos)
			return (NULL);
	}
	return (NULL);
}
