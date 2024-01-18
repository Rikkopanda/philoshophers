/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rik <rik@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:34:17 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/18 10:41:07 by rik              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_loop(t_data *data, int *i, int *done_count)
{
	t_philo	*cur_philo;

	cur_philo = (*data).philos_ptr;
	while (*i < (*data).n_of_philos)
	{
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
