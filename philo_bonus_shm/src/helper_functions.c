/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:35:03 by rik               #+#    #+#             */
/*   Updated: 2024/01/16 12:59:54 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	writing(char nbr_str1[1000], char nbr_str2[1000],
			char *print_str, int print_len[2])
{
	if (write(1, nbr_str2, print_len[1]) <= 0)
		return ;
	if (write(1, " ", 1) <= 0)
		return ;
	if (write(1, nbr_str1, print_len[0]) <= 0)
		return ;
	if (write(1, " ", 1) <= 0)
		return ;
	if (write(1, print_str, ft_strlen(print_str)) <= 0)
		return ;
}

void	printfunc(t_philo *philo, struct timeval *tv, char *print_str)
{
	sem_wait((*philo).data->print_sem);
	(*philo).print_len[1] = ft_utoa_1000((*philo).philo_nbr, (*philo).nbr_str2);
	gettimeofday(tv, NULL);
	(*philo).current_time
		= ((*tv).tv_sec * 1000) + ((*tv).tv_usec / 1000) - (*philo).start_time;
	(*philo).print_len[0]
		= ft_utoa_1000((*philo).current_time, (*philo).nbr_str1);
	writing((*philo).nbr_str1, (*philo).nbr_str2, print_str,
		(*philo).print_len);
	sem_post((*philo).data->print_sem);
}
// philo's have slightly different start times,
// hence time result in printing is different
//void set_global_start(t_data *data)
//{
//	struct timeval	tv;
//	gettimeofday(&tv, NULL);
//	(*data).start_time = ((tv).tv_sec * 1000) + ((tv).tv_usec / 1000);
//}
//set_global_start(data);

void	free_data(t_data *data)
{
	free((*data).forks_sem_name);
	free((*data).print_sem_name);
	free((*data).died_sem_name);
	sem_close((*data).died_sem);
	sem_close((*data).print_sem);
	sem_close((*data).forks_sem);
	free((*data).pids);
}
