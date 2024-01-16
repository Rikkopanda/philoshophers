/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:05:04 by rik               #+#    #+#             */
/*   Updated: 2024/01/16 12:59:45 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data(t_data *data, int argc, char **argv)
{
	int			i;
	long long	*argu_nbrs;

	if (argc < 5 || argc > 6)
		return (-1);
	argu_nbrs = malloc(sizeof(long long) * argc - 1);
	i = 0;
	while (i < argc - 1)
	{
		argu_nbrs[i] = ft_atoi(argv[i + 1]);
		i++;
	}
	(*data).n_of_philos = argu_nbrs[0];
	(*data).fork_n = argu_nbrs[0];
	(*data).time_to_die = argu_nbrs[1];
	(*data).time_to_eat = argu_nbrs[2];
	(*data).time_to_sleep = argu_nbrs[3];
	*(*data).stop_bool_shared = 0;
	(*data).pids = malloc(sizeof(pid_t) * ((*data).n_of_philos));
	if (argc > 5)
		(*data).n_times_to_eat_philo = argu_nbrs[4];
	else
		(*data).n_times_to_eat_philo = -1;
	free(argu_nbrs);
	return (0);
}

int	init_semaphores(t_data *data)
{
	(*data).forks_sem_name = ft_strdup("/fork_sem");
	(*data).print_sem_name = ft_strdup("/print_sem");
	(*data).died_sem_name = ft_strdup("/died_sem");
	open_named_semaphore(&(*data).forks_sem,
		&(*data).forks_sem_name, (*data).fork_n);
	open_named_semaphore(&(*data).print_sem, &(*data).print_sem_name, 1);
	open_named_semaphore(&(*data).died_sem, &(*data).died_sem_name, 1);
	return (0);
}
