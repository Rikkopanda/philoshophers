/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:31:45 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/23 14:31:12 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	phil_eat(t_philo *philo, struct timeval *tv)
{
	pthread_mutex_lock(&philo->data->die_lock);
	{
		if (philo->data->died_bool == 1)
		{
			pthread_mutex_unlock(&philo->data->die_lock);
			unlock_both(philo);
			pthread_exit(NULL);
		}
		printfunc(philo, tv, "is eating\n");
		gettimeofday(tv, NULL);
		philo->last_meal_ms = ((*tv).tv_sec * 1000) + ((*tv).tv_usec / 1000);
	}
	pthread_mutex_unlock(&philo->data->die_lock);
	usleep(philo->data->time_to_eat * 1000);
	philo->eat_counter++;
	return (0);
}

int	phil_sleep(t_philo *philo, struct timeval *tv)
{
	exit_if_died_or_done(philo);
	printfunc(philo, tv, "is sleeping\n");
	usleep(philo->data->time_to_sleep * 1000);
	usleep(GETTING_OUT_OF_BED);
	return (0);
}

int	pick_forks(t_philo *philo, struct timeval *tv,
	pthread_mutex_t *first, pthread_mutex_t *second)
{
	if(exit_if_died_or_done(philo) == 1)
		pthread_exit(NULL);
	{
		pthread_mutex_lock(first);
		if(exit_if_died_or_done(philo) == 1)
		{
			pthread_mutex_unlock(first);
			pthread_exit(NULL);
		}

		printfunc(philo, tv, "has taken a fork\n");
	}
	{
		pthread_mutex_lock(second);
		exit_if_died_or_done(philo);
		printfunc(philo, tv, "has taken a fork\n");
	}
	return (0);
}

int	try_pick_forks(t_philo *philo, struct timeval *tv, int what_lock_sequence)
{
	if (what_lock_sequence != 0)
	{
		if (pick_forks(philo, tv, (*philo).left_fork,
				(*philo).right_fork))
			return (END_SIMULATION);
		exit_if_died_or_done(philo);
	}
	else
	{
		if (pick_forks(philo, tv, (*philo).right_fork,
				(*philo).left_fork))
			return (END_SIMULATION);
		exit_if_died_or_done(philo);
	}
	return (0);
}
