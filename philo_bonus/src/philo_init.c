/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:07:05 by rik               #+#    #+#             */
/*   Updated: 2024/01/17 11:41:31 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	personal_semaphores(t_philo *philo)
{
	char	nbr_str[1000];

	nbr_str[0] = '\0';
	ft_utoa_1000((*philo).philo_nbr, nbr_str);
	{
		make_semaphore(&(*philo).current_time_sem_name, nbr_str, "/time_sem_");
		make_semaphore(&(*philo).done_sem_name, nbr_str, "/done_sem_");
		make_semaphore(&(*philo).next_meal_sem_name, nbr_str, "/next_meal_sem");
		sem_init(&(*philo).eat_cnt_sem, THREAD_SHARED, 1);
		sem_init(&(*philo).holding_one_fork_sem, THREAD_SHARED, 1);
	}
	{
		open_named_semaphore(&(*philo).done_sem, &(*philo).done_sem_name, 1);
		open_named_semaphore(&(*philo).current_time_sem,
			&(*philo).current_time_sem_name, 1);
		open_named_semaphore(&(*philo).next_meal_sem,
			&(*philo).next_meal_sem_name, 1);
	}
	return (0);
}

void	init_philo_data1(t_philo *philo, t_data *data, int *process_i)
{
	(*philo).done_bool = 0;
	(*philo).philo_nbr = *process_i + 1;
	(*philo).data = data;
}

void	init_philo_data2(t_philo *philo)
{
	(*philo).next_meal = philo->data->start_time + ((*philo).data->time_to_die);
	(*philo).eat_counter = 0;
	(*philo).holding_one_fork = 0;
}
