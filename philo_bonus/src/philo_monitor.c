/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:34:24 by rik               #+#    #+#             */
/*   Updated: 2024/01/17 12:20:22 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		sem_wait(philo->data->stop_sem);
		sem_wait(philo->next_meal_sem);
		if (get_time(&tv) > philo->next_meal)
		{
			when_died(philo, &tv);
			break ;
		}
		sem_post(philo->data->stop_sem);
		sem_post(philo->next_meal_sem);
	}
	pthread_exit(NULL);
	return (NULL);
}
// printf("hello from monitor..\n");
// printf("%d \n", philo->eat_counter);
// printf("next %u \n", philo->next_meal);
// printf("current time %u \n", get_time(&tv));