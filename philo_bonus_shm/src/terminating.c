/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminating.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:02:28 by rik               #+#    #+#             */
/*   Updated: 2024/01/16 13:01:39 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_for_child_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < (*data).n_of_philos)
	{
		wait(NULL);
		i++;
	}
}

void	clean_up(t_data *data)
{
	if (sem_unlink((*data).forks_sem_name) == -1)
		perror("sem_link -1: ");
	if (sem_unlink((*data).print_sem_name) == -1)
		perror("sem_link -1: ");
	if (sem_unlink((*data).died_sem_name) == -1)
		perror("sem_link -1: ");
	free_data(data);
}
