/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:38:06 by rik               #+#    #+#             */
/*   Updated: 2024/01/17 12:06:05 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_inherited_data(t_data *data)
{
	free_data(data);
}

void	free_philo_data(t_philo *philo)
{
	sem_close((*philo).done_sem);
	sem_close((*philo).current_time_sem);
	sem_close((*philo).next_meal_sem);
	sem_destroy(&(*philo).eat_cnt_sem);
	sem_destroy(&(*philo).holding_one_fork_sem);
	{
		free((*philo).current_time_sem_name);
		free((*philo).done_sem_name);
		free((*philo).next_meal_sem_name);
	}
}

int	check_done(t_philo *philo)
{
	sem_wait((*philo).done_sem);
	if (philo->done_bool == 1)
		return (sem_post((*philo).done_sem), 1);
	sem_post((*philo).done_sem);
	sem_wait(philo->data->stop_sem);
	sem_post(philo->data->stop_sem);
	return (0);
}
