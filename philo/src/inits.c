/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:22:26 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/23 12:03:35 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_locks(t_data *data)
{
	int				i;
	pthread_mutex_t	*fork;

	i = 0;
	fork = data->forks;
	while (i < (*data).n_of_philos)
	{
		if (pthread_mutex_init(fork, NULL) != 0)
			return (-1);
		fork += 1;
		i++;
	}
	if (pthread_mutex_init(&(*data).die_lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&(*data).start_signal, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&(*data).done_lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&(*data).time_since_meal, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&(*data).print_lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&(*data).start_time_lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&(*data).cnt_to_start_th_lock, NULL) != 0)
		return (-1);
	return (0);
}

int	init_data(t_philo **philos, t_data *data)
{
	int		i;

	if ((*philos = malloc(sizeof(t_philo) * (*data).n_of_philos)) == NULL)
		return (-1);
	if ((data->forks = malloc(sizeof(pthread_mutex_t) * (*data).n_of_philos)) == NULL)
		return (free(*philos), -1);
	(*data).cnt_to_start_th = 0;
	(*data).end = 0;
	(*data).died_bool = 0;
	(*data).philos_ptr = *philos;
	i = 1;
	while (i <= (*data).n_of_philos)
	{
		(*philos)[i - 1].data = data;
		(*philos)[i - 1].done_bool = 0;
		(*philos)[i - 1].philo_nbr = i;
		(*philos)[i - 1].time_since_meal = 0;
		i++;
	}
	return (0);
}

int	init_args_data(t_data *data, int argc, char **argv)
{
	int				i;
	unsigned int	*argu_nbrs;

	if (argc < 5 || argc > 6)
		return (printf("error parsing\n"), -1);
	argu_nbrs = malloc(sizeof(long long) * argc - 1);
	i = 0;
	while (i < argc - 1)
	{
		argu_nbrs[i] = ft_atoi(argv[i + 1]);
		if(argu_nbrs[i] == 0)
			return (printf("error parsing\n"), free(argu_nbrs), -1);
		i++;
	}
	(*data).n_of_philos = argu_nbrs[0];
	(*data).time_to_die = argu_nbrs[1];
	(*data).time_to_eat = argu_nbrs[2];
	(*data).time_to_sleep = argu_nbrs[3];
	if (argc > 5)
		(*data).n_times_to_eat_philo = argu_nbrs[4];
	else
		(*data).n_times_to_eat_philo = -1;
	free(argu_nbrs);
	return (0);
}
