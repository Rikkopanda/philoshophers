/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:34:23 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/17 11:27:13 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	printfunc(t_philo *philo, struct timeval *tv, char *print_str)
{
	(*philo).print_len[1] = ft_utoa_1000((*philo).philo_nbr, (*philo).nbr_str2);
	pthread_mutex_lock((*philo).data->print_lock);
	gettimeofday(tv, NULL);
	(*philo).print_len[0]
		= ft_utoa_1000(((*tv).tv_sec * 1000) + ((*tv).tv_usec / 1000)
			- philo->data->start_time, (*philo).nbr_str1);
	writing((*philo).nbr_str1, (*philo).nbr_str2, print_str,
		(*philo).print_len);
	pthread_mutex_unlock((*philo).data->print_lock);
}

void	writing(char nbr_str1[1000], char nbr_str2[1000],
			char *print_str, int print_len[2])
{
	if (write(1, nbr_str1, print_len[0]) <= 0)
		return ;
	if (write(1, " ", 1) <= 0)
		return ;
	if (write(1, nbr_str2, print_len[1]) <= 0)
		return ;
	if (write(1, " ", 1) <= 0)
		return ;
	if (write(1, print_str, ft_strlen(print_str)) <= 0)
		return ;
}

//void set_global_start(t_data *data)
//{
//	struct timeval	tv;
//	gettimeofday(&tv, NULL);
//	(*data).start_time = ((tv).tv_sec * 1000) + ((tv).tv_usec / 1000);
//}
//set_global_start(data);

//void	printfunc2(t_philo *philo, char *print_str)
//{
//	pthread_mutex_lock((*philo).data->print_lock);
//	printf("philo %d %s", philo->philo_nbr, print_str);
//	pthread_mutex_unlock((*philo).data->print_lock);
//}
