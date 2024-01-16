/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:34:24 by rik               #+#    #+#             */
/*   Updated: 2024/01/16 12:50:50 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define BREAK_DEADLOCK 4

void	when_died(t_philo *philo, struct timeval *tv)
{
	philo->status = DIED;
	sem_post(philo->next_meal_sem);
	sem_wait(philo->done_sem);
	philo->done_bool = 1;
	sem_post(philo->done_sem);
	printfunc(philo, tv, "died\n");
	sem_post(philo->data->stop_sem);
}
//sem_wait(&(*philo).holding_one_fork_sem);
//if ((*philo).holding_one_fork == 1)
//{
//	sem_post(&(*philo).holding_one_fork_sem);
//	exit(BREAK_DEADLOCK);
//}
//sem_post(&(*philo).holding_one_fork_sem);

void	when_enough(t_philo *philo)
{
	sem_post(&(*philo).eat_cnt_sem);
	philo->status = DONE_EATING;
	sem_wait(philo->done_sem);
	philo->done_bool = 1;
	sem_post(philo->done_sem);
	sem_post(philo->data->stop_sem);
}

void	*monitoring(void *ptr)
{
	t_philo			*philo;
	struct timeval	tv;

	philo = (t_philo *)ptr;
	while (1)
	{
		sem_wait(&(*philo).eat_cnt_sem);
		if (philo->eat_counter == philo->data->n_times_to_eat_philo)
		{
			when_enough(philo);
			break ;
		}
		sem_post(&(*philo).eat_cnt_sem);
		sem_wait(philo->next_meal_sem);
		if (get_time(&tv) > philo->next_meal)
		{
			when_died(philo, &tv);
			break ;
		}
		sem_post(philo->next_meal_sem);
		usleep(300);
	}
	pthread_exit(NULL);
	return (NULL);
}
// printf("hello from monitor..\n");
// printf("%d \n", philo->eat_counter);
// printf("next %u \n", philo->next_meal);
// printf("current time %u \n", get_time(&tv));