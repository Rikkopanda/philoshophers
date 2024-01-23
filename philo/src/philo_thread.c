/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:33:56 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/23 14:28:57 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	eat(t_philo *philo, struct timeval *tv)
{
	if(exit_if_died_or_done(philo) == 1)
		pthread_exit(NULL);
	if (try_pick_forks(philo, tv, (*philo).philo_nbr % 2) == END_SIMULATION)
		return (END_SIMULATION);
	phil_eat(philo, tv);
	pthread_mutex_unlock((*philo).left_fork);
	pthread_mutex_unlock((*philo).right_fork);
	return (0);
}

/*
	exits when philo has eaten enought times or one philo has died,
	this is checked and set in the monitoring thread.
*/

static void	think(t_philo *philo, struct timeval *tv)
{
	if(exit_if_died_or_done(philo) == 1)
		pthread_exit(NULL);
	printfunc(philo, tv, "is thinking\n");
}

void	*loop(t_philo *philo, struct timeval *tv)
{
	while (1)
	{
		eat(philo, tv);
		phil_sleep(philo, tv);
		think(philo, tv);
	}
	return ((void *)NEVER_REACHES_THIS);
}

/*
	initializes the philo data, starts the loop.
	waits for all threads to be created;
	start_signal lock gets unlocked each thread.
*/

void	set_philo_data(t_philo *philo)
{
	philo->eat_counter = 0;
}

void	*routine(void *ptr)
{
	t_philo			*philo;
	struct timeval	tv;

	philo = (t_philo *)ptr;
	set_philo_data(philo);
	assign_fork_ptrs(philo);
	pthread_mutex_lock(&philo->data->start_signal);
	//printfunc(philo, &tv, "check\n");
	pthread_mutex_unlock(&philo->data->start_signal);
	if (philo->data->n_of_philos == 1)
		return (printfunc(philo, &tv, "died"), (void *)ONLY_ONE_PHILO);
	//usleep(30000);
	if ((*philo).philo_nbr % 2 != 0)
		usleep(WAIT_PHILO);
	return (loop(philo, &tv));
}
