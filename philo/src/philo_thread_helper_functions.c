/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_helper_functions.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:34:02 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/23 14:27:36 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	assign_time_since_last_meal(t_philo *philo, struct timeval *tv)
{
	gettimeofday(tv, NULL);
	(*philo).current_time = ((*tv).tv_sec * 1000) + ((*tv).tv_usec / 1000);
	pthread_mutex_lock(&(*philo).data->time_since_meal);
	(*philo).time_since_meal = (*philo).current_time - philo->last_meal_ms;
	pthread_mutex_unlock(&(*philo).data->time_since_meal);
}

void	assign_fork_ptrs(t_philo *philo)
{
	if (philo->philo_nbr
		< philo->data->n_of_philos)
	{
		philo->right_fork
			= philo->data->forks + philo->philo_nbr - 1;
		philo->left_fork
			= philo->data->forks + philo->philo_nbr;
	}
	else if (philo->philo_nbr
		== philo->data->n_of_philos)
	{
		philo->right_fork
			= philo->data->forks + philo->philo_nbr - 1;
		philo->left_fork
			= philo->data->forks + 0;
	}
}

void	unlock_both(t_philo *philo)
{
	pthread_mutex_unlock((*philo).left_fork);
	pthread_mutex_unlock((*philo).right_fork);
}

int	exit_if_died_or_done(t_philo *philo)
{
	if (philo->eat_counter == philo->data->n_times_to_eat_philo)
	{
		pthread_mutex_lock(&(*philo).data->done_lock);
		(*philo).done_bool = 1;
		pthread_mutex_unlock(&(*philo).data->done_lock);
		return (1);
	}
	pthread_mutex_lock(&(*philo).data->die_lock);
	if ((*philo).data->died_bool == 1)
	{
		pthread_mutex_unlock(&(*philo).data->die_lock);
		return (1);
	}
	pthread_mutex_unlock(&(*philo).data->die_lock);
	return (0);
}
