/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:31:45 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/17 09:58:44 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	phil_eat(t_philo *philo, struct timeval *tv)
{
	pthread_mutex_lock(philo->data->die_lock);
	if (philo->data->died_bool == 1)
		return (pthread_mutex_unlock(philo->data->die_lock), -1);
	printfunc(philo, tv, "is eating\n");
	gettimeofday(tv, NULL);
	philo->last_meal_ms = ((*tv).tv_sec * 1000) + ((*tv).tv_usec / 1000);
	assign_time_since_last_meal(philo, tv);
	pthread_mutex_unlock(philo->data->die_lock);
	usleep(philo->data->time_to_eat * 1000);
	philo->eat_counter++;
	return (0);
}

void	phil_sleep(t_philo *philo, struct timeval *tv)
{
	printfunc(philo, tv, "is sleeping\n");
	usleep(philo->data->time_to_sleep * 1000);
}

int	pick_forks(t_philo *philo, struct timeval *tv,
	pthread_mutex_t *first, pthread_mutex_t *second)
{
	assign_time_since_last_meal(philo, tv);
	if (!check_continue(philo))
		return (END_SIMULATION);
	{
		pthread_mutex_lock(first);
		assign_time_since_last_meal(philo, tv);
		if (!check_continue(philo))
			return (pthread_mutex_unlock(first), END_SIMULATION);
		printfunc(philo, tv, "has taken a fork\n");
	}
	{
		pthread_mutex_lock(second);
		assign_time_since_last_meal(philo, tv);
		if (!check_continue(philo))
			return (unlock_both(philo), END_SIMULATION);
		printfunc(philo, tv, "has taken a fork\n");
	}
	return (0);
}

int	try_pick_forks(t_philo *philo, struct timeval *tv, int what_lock_sequence)
{
	if (what_lock_sequence != 0)
	{
		if (pick_forks(philo, tv, &(*philo).left_fork->lock,
				&(*philo).right_fork->lock))
			return (END_SIMULATION);
		assign_time_since_last_meal(philo, tv);
		if (!check_continue(philo))
			return (unlock_both(philo), END_SIMULATION);
	}
	else
	{
		if (pick_forks(philo, tv, &(*philo).right_fork->lock,
				&(*philo).left_fork->lock))
			return (END_SIMULATION);
		assign_time_since_last_meal(philo, tv);
		if (!check_continue(philo))
			return (unlock_both(philo), END_SIMULATION);
	}
	return (0);
}
