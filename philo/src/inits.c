/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rik <rik@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:22:26 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/21 16:00:21 by rik              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_locks(t_fork *forks, t_data *data)
{
	int	i;

	i = 0;
	while (i < (*data).n_of_philos)
	{
		if (pthread_mutex_init(&forks->lock, NULL) != 0)
			return (-1);
		forks += 1;
		i++;
	}
	if (pthread_mutex_init((*data).die_lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init((*data).done_lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init((*data).time_since_meal, NULL) != 0)
		return (-1);
	if (pthread_mutex_init((*data).print_lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init((*data).start_time_lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init((*data).cnt_to_start_th_lock, NULL) != 0)
		return (-1);
	return (0);
}

void	m_fail_frees(t_philo **philos, t_data *data, int x)
{
	free(*philos);
	if (x < 2)
		return ;
	free((*data).die_lock);
	if (x < 3)
		return ;
	free((*data).done_lock);
	if (x < 4)
		return ;
	free((*data).time_since_meal);
	if (x < 5)
		return ;
	free((*data).print_lock);
	if (x < 6)
		return ;
	free((*data).start_time_lock);
	if (x < 7)
		return ;
	free((*data).cnt_to_start_th_lock);
}

int	init_data(t_philo **philos, t_data *data)
{
	t_fork	*forks;
	int		i;

	if ((*philos = malloc(sizeof(t_philo) * (*data).n_of_philos)) == NULL)
		return (-1);
	if ((forks = malloc(sizeof(t_fork) * (*data).n_of_philos)) == NULL)
		return (m_fail_frees(philos, data, 1), -1);
	if (((*data).die_lock = malloc(sizeof(pthread_mutex_t))) == NULL)
		return (m_fail_frees(philos, data, 2), -1);
	if (((*data).done_lock = malloc(sizeof(pthread_mutex_t))) == NULL)
		return (m_fail_frees(philos, data, 3), -1);
	if (((*data).time_since_meal = malloc(sizeof(pthread_mutex_t))) == NULL)
		return (m_fail_frees(philos, data, 4), -1);
	if (((*data).print_lock = malloc(sizeof(pthread_mutex_t))) == NULL)
		return (m_fail_frees(philos, data, 5), -1);
	if (((*data).start_time_lock = malloc(sizeof(pthread_mutex_t))) == NULL)
		return (m_fail_frees(philos, data, 6), -1);
	if (((*data).cnt_to_start_th_lock = malloc(sizeof(pthread_mutex_t))) == NULL)
		return (m_fail_frees(philos, data, 7), -1);
	(*data).forks_ptr = forks;
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
		if(argu_nbrs[i] <= 0)
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
