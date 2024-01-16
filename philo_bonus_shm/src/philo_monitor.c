/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:34:24 by rik               #+#    #+#             */
/*   Updated: 2024/01/16 13:30:08 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_stop_bool(t_philo *philo)
{
	sem_wait(philo->data->died_sem);
	if (*philo->data->stop_bool_shared == 1)
		return (sem_post(philo->data->died_sem), 1);
	sem_post(philo->data->died_sem);
	return (0);
}

int	check_eat_count(t_philo *philo)
{
	sem_wait(&(*philo).eat_cnt_sem);
	if (philo->eat_counter == philo->data->n_times_to_eat_philo)
	{
		when_enough(philo);
		return (1);
	}
	sem_post(&(*philo).eat_cnt_sem);
	return (0);
}

int	check_died_monitor(t_philo *philo, struct timeval *tv)
{
	sem_wait(philo->next_meal_sem);
	if (get_time(tv) > philo->next_meal)
	{
		when_died(philo, tv);
		return (1);
	}
	sem_post(philo->next_meal_sem);
	return (0);
}

void	*monitoring(void *ptr)
{
	t_philo			*philo;
	struct timeval	tv;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (check_stop_bool(philo) == 1)
			break ;
		if (check_eat_count(philo) == 1)
			break ;
		if (check_stop_bool(philo) == 1)
			break ;
		if (check_died_monitor(philo, &tv) == 1)
			break ;
		usleep(300);
	}
	pthread_exit(NULL);
	return (NULL);
}
// printf("hello from monitor..\n");
// printf("%d \n", philo->eat_counter);
// printf("next %u \n", philo->next_meal);
// printf("current time %u \n", get_time(&tv));