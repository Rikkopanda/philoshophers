/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:18:45 by rik               #+#    #+#             */
/*   Updated: 2024/01/17 12:18:37 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	forking(t_data *data, pid_t *p, int *procces_i)
{
	*procces_i = 0;
	while (*procces_i < (*data).n_of_philos)
	{
		*p = fork();
		if (!*p)
			break ;
		if (*p)
			(*data).pids[*procces_i] = *p;
		(*procces_i)++;
	}
	return (0);
}

void	init_start_time(t_data *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	(*data).start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pid_t		p;
	int			process_i;
	int			status;	

	init_data(&data, argc, argv);
	init_semaphores(&data);
	init_start_time(&data);
	forking(&data, &p, &process_i);
	if (!p)
	{
		status = philo_process(process_i, &data);
		exit(status);
	}
	wait_for_child_processes(&data);
	clean_up(&data);
	return (0);
}

//			assign_time_since_last_meal(&data.philos_ptr[i], &tv);
//			//printf("hellofrom checker1\n");
//			if (*data.philos_ptr[i].time_since_meal > data.time_to_die)
//			{
//				//printf("hellofrom checker\n");
//				sem_wait(data.died_sem);
//				*data.died_bool = 1;
//				sem_post(data.died_sem);