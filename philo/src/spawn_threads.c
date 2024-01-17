/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:33:37 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/17 11:18:06 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_start_time(t_data *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	(*data).start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int	create_philos(t_philo **philos, t_data *data)
{
	int	i;

	init_data(philos, data);
	init_locks((*data).forks_ptr, data);
	pthread_create(&(*data).monitor_th_id, NULL, monitoring, data);
	if (!philos)
		return (-1);
	init_start_time(data);
	i = 1;
	while (i <= (*data).n_of_philos)
	{
		pthread_create(&(*philos)[i - 1].th_id,
			NULL, routine, &(*philos)[i - 1]);
		i++;
	}
	return (1);
}
