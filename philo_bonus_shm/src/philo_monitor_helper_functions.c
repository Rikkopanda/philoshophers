/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor_helper_functions.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:34:24 by rik               #+#    #+#             */
/*   Updated: 2024/01/16 13:30:15 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	when_died(t_philo *philo, struct timeval *tv)
{
	sem_post(philo->next_meal_sem);
	philo->status = DIED;
	sem_wait(philo->data->died_sem);
	*philo->data->stop_bool_shared = 1;
	sem_post(philo->data->died_sem);
	printfunc(philo, tv, "died\n");
}

void	when_enough(t_philo *philo)
{
	sem_post(&(*philo).eat_cnt_sem);
	philo->status = DONE_EATING;
	sem_wait(philo->done_sem);
	philo->done_bool = 1;
	sem_post(philo->done_sem);
}
