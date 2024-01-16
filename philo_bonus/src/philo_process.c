/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:34:27 by rik               #+#    #+#             */
/*   Updated: 2024/01/16 13:38:46 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_loop(t_philo *philo, t_data *data, struct timeval *tv)
{
	if ((*philo).philo_nbr % 2 != 0)
		usleep(400);
	while (1)
	{
		if (phil_pick_forks(philo, data, tv) == -1)
			break ;
		phil_eat(philo, tv);
		sem_post((*data).forks_sem);
		sem_post((*data).forks_sem);
		if (check_done(philo))
			break ;
		printfunc(philo, tv, "is sleeping\n");
		usleep((*data).time_to_sleep * 1000);
		if (check_done(philo))
			break ;
		printfunc(philo, tv, "is thinking\n");
	}
}
//printfunc(philo, tv, "ok bye bye\n");

int	philo_process(int process_i, t_data *data)
{
	struct timeval		tv;
	t_philo				philo;

	init_philo_data1(&philo, data, &process_i);
	personal_semaphores(&philo);
	init_philo_data2(&philo, &tv);
	pthread_create(&philo.monitor_th_id, NULL, monitoring, &philo);
	{
		philo_loop(&philo, data, &tv);
	}
	pthread_join(philo.monitor_th_id, NULL);
	free_philo_data(&philo);
	free_inherited_data(data);
	return (philo.status);
}
