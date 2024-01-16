/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:34:41 by rik               #+#    #+#             */
/*   Updated: 2024/01/16 12:41:15 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned	int	get_time(struct timeval *tv)
{
	unsigned int	time;

	gettimeofday(tv, NULL);
	time = ((*tv).tv_sec * 1000) + ((*tv).tv_usec / 1000);
	return (time);
}

void	phil_eat(t_philo *philo, struct timeval *tv)
{
	printfunc(philo, tv, "is eating😃\n");
	{
		sem_wait(philo->next_meal_sem);
		usleep(philo->data->time_to_eat * 1000);
		(*philo).current_time = get_time(tv);
		philo->next_meal = (*philo).current_time + (philo->data->time_to_die);
		sem_post(philo->next_meal_sem);
	}
	sem_wait(&(*philo).eat_cnt_sem);
	philo->eat_counter += 1;
	sem_post(&(*philo).eat_cnt_sem);
}

int	phil_pick_forks(t_philo *philo, t_data *data, struct timeval *tv)
{
	{
		sem_wait((*data).forks_sem);
		if (check_done(philo))
			return (sem_post((*data).forks_sem), -1);
		printfunc(philo, tv, "has taken a fork\n");
	}
	{
		sem_wait((*data).forks_sem);
		if (check_done(philo))
			return (sem_post((*data).forks_sem),
				sem_post((*data).forks_sem), -1);
		printfunc(philo, tv, "has taken a fork\n");
	}
	return (0);
}
//{
//	sem_wait(&(*philo).holding_one_fork_sem);
//	(*philo).holding_one_fork = 1;
//	sem_post(&(*philo).holding_one_fork_sem);
//}
//{
//	sem_wait(&(*philo).holding_one_fork_sem);
//	(*philo).holding_one_fork = 0;
//	sem_post(&(*philo).holding_one_fork_sem);
//}