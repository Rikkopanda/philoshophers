/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rik <rik@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:33:56 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/21 15:34:07 by rik              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


/*
	eat()
	{
		if(!check_continue)
			return
		try_to_pick_forks()
		assign_last+next_meal()
		usleep(EAT_TIME)
		eat_counter++;
		unlock_forks
	}
	sleep()
	think()
*/

// static int	eat()

/*
	exits when philo has eaten enought times or one philo has died,
	this is checked and set in the monitoring thread.
*/
void	*loop(t_philo *philo, struct timeval *tv)
{
	while (1)
	{
		assign_time_since_last_meal(philo, tv);
		if (!check_continue(philo))
			return ((void *)END_SIMULATION);
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
		usleep(GETTING_OUT_OF_BED);
		assign_time_since_last_meal(philo, tv);
		if (!check_continue(philo))
			return ((void *)END_SIMULATION);
		printfunc(philo, tv, "is thinking\n");
	}
	return ((void *)NEVER_REACHES_THIS);
}

/*
	initializes the philo data, starts the loop.
	waits for all threads to be created;
	start_signal lock gets unlocked each thread.
*/
void	*routine(void *ptr)
{
	t_philo			*philo;
	struct timeval	tv;

	// lock 	start_signal
	// unlock 	start_signal
	philo = (t_philo *)ptr;
	set_data_philo(philo);// before thread
	assign_fork_ptrs(philo);// before thread
	if (philo->data->n_of_philos == 1)
		return (printfunc(philo, &tv, "died"), (void *)ONLY_ONE_PHILO);
	if ((*philo).philo_nbr % 2 != 0)
		usleep(WAIT_PHILO);
	return (loop(philo, &tv));
}

// void	wait_until_start_sign(t_philo *philo, struct timeval *tv)
// {
// 	pthread_mutex_lock(philo->data->cnt_to_start_th_lock);
// 	philo->data->cnt_to_start_th++;
// 	pthread_mutex_unlock(philo->data->cnt_to_start_th_lock);
// 	while (1)
// 	{
// 		pthread_mutex_lock(philo->data->cnt_to_start_th_lock);
// 		if (philo->data->cnt_to_start_th == philo->data->n_of_philos)
// 		{
// 			gettimeofday(tv, NULL);
// 			pthread_mutex_lock(philo->data->start_time_lock);
// 			philo->data->start_time = ((*tv).tv_sec * 1000)
// 				+ ((*tv).tv_usec / 1000);
// 			pthread_mutex_unlock(philo->data->start_time_lock);
// 			pthread_mutex_unlock(philo->data->cnt_to_start_th_lock);
// 			break ;
// 		}
// 		pthread_mutex_unlock(philo->data->cnt_to_start_th_lock);
// 	}
// }
