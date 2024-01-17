/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor_helper_functions.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:34:24 by rik               #+#    #+#             */
/*   Updated: 2024/01/17 12:20:16 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	printfunc_monitor(t_philo *philo, struct timeval *tv, char *print_str)
{
	int		print_len[2];
	int		current_time;
	char	nbr_str1[1000];
	char	nbr_str2[1000];

	print_len[1] = ft_utoa_1000((*philo).philo_nbr, nbr_str1);
	sem_wait((*philo).data->print_sem);
	gettimeofday(tv, NULL);
	current_time = ((*tv).tv_sec * 1000) + ((*tv).tv_usec / 1000)
		- philo->data->start_time;
	print_len[0] = ft_utoa_1000(current_time, nbr_str2);
	writing(nbr_str2, nbr_str1, print_str, print_len);
	sem_post((*philo).data->print_sem);
	return (0);
}

void	when_died(t_philo *philo, struct timeval *tv)
{
	philo->status = DIED;
	sem_post(philo->next_meal_sem);
	sem_wait(philo->done_sem);
	philo->done_bool = 1;
	sem_post(philo->done_sem);
	usleep(1000);
	printfunc_monitor(philo, tv, "died\n");
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
