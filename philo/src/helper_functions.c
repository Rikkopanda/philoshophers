/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:34:23 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/23 13:02:41 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	printfunc(t_philo *philo, struct timeval *tv, char *print_str)
{
	int	current_time;

	gettimeofday(tv, NULL);
	current_time = ((*tv).tv_sec * 1000 + ((*tv).tv_usec / 1000))
			- philo->data->start_time;
	pthread_mutex_lock(&(*philo).data->print_lock);
	printf("%d %d %s", current_time, (*philo).philo_nbr, print_str);
	pthread_mutex_unlock(&(*philo).data->print_lock);
}
