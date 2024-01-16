/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:33:56 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/16 18:38:00 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*loop(t_philo *philo, struct timeval *tv)
{
	while (1)
	{
		if (try_pick_forks(philo, tv, (*philo).philo_nbr % 2) == END_SIMULATION)
			return ((void *)END_SIMULATION);
		if (phil_eat(philo, tv) == END_SIMULATION)
			return (unlock_both(philo), (void *)END_SIMULATION);
		pthread_mutex_unlock(&(*philo).left_fork->lock);
		pthread_mutex_unlock(&(*philo).right_fork->lock);
		assign_time_since_last_meal(philo, tv);
		if (!check_continue(philo))
			return ((void *)END_SIMULATION);
		phil_sleep(philo, tv);
		assign_time_since_last_meal(philo, tv);
		if (!check_continue(philo))
			return ((void *)END_SIMULATION);
		printfunc(philo, tv, "is thinking🤔\n");
	}
	return ((void *)NEVER_REACHES_THIS);
}

void	wait_until_start_sign(t_philo *philo, struct timeval *tv)
{
	pthread_mutex_lock(philo->data->cnt_to_start_th_lock);
	philo->data->cnt_to_start_th++;
	pthread_mutex_unlock(philo->data->cnt_to_start_th_lock);
	while (1)
	{
		pthread_mutex_lock(philo->data->cnt_to_start_th_lock);
		if (philo->data->cnt_to_start_th == philo->data->n_of_philos)
		{
			gettimeofday(tv, NULL);
			pthread_mutex_lock(philo->data->start_time_lock);
			philo->data->start_time = ((*tv).tv_sec * 1000)
				+ ((*tv).tv_usec / 1000);
			pthread_mutex_unlock(philo->data->start_time_lock);
			pthread_mutex_unlock(philo->data->cnt_to_start_th_lock);
			break ;
		}
		pthread_mutex_unlock(philo->data->cnt_to_start_th_lock);
		usleep(1);
	}
}

void	*routine(void *ptr)
{
	t_philo			*philo;
	struct timeval	tv;

	philo = (t_philo *)ptr;
	set_data_philo(philo);
	assign_fork_ptrs(philo);
	if (philo->data->n_of_philos == 1)
		return (printfunc(philo, &tv, "died"), (void *)ONLY_ONE_PHILO);
	wait_until_start_sign(philo, &tv);
	if ((*philo).philo_nbr % 2 != 0)
		usleep(WAIT_PHILO);
	return (loop(philo, &tv));
}
