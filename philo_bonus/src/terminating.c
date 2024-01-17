/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminating.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:02:28 by rik               #+#    #+#             */
/*   Updated: 2024/01/17 12:18:45 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_done_check_list(pid_t **already_destroyed_or_done, t_data *data)
{
	int	i;

	*already_destroyed_or_done
		= malloc(sizeof(pid_t) * (data->n_of_philos * 2));
	i = 0;
	while (i < data->n_of_philos * 2)
	{
		(*already_destroyed_or_done)[i] = (pid_t)0;
		i++;
	}
}

void	wait_for_child_processes(t_data *data)
{
	int		i;
	int		status;
	pid_t	ret_pid;
	pid_t	*already_destroyed_or_done;

	init_done_check_list(&already_destroyed_or_done, data);
	i = (*data).n_of_philos - 1;
	while (i >= 0)
	{
		ret_pid = wait(&status);
		i--;
		if (WEXITSTATUS(status) == DONE_EATING)
			continue ;
		destroy_all(data, ret_pid, already_destroyed_or_done);
	}
	free(already_destroyed_or_done);
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
	sem_close((*data).stop_sem);
}
// printf("returned %d \n", ret_pid);
// printf ("status = %d\n", WEXITSTATUS(status));

// if first 2 returing childs are done eating, 3rd died; does destroy all kill
// send signal to the first 2?

int	check_if_done(int *i, int *j,
		pid_t *already_destroyed_or_done, t_data *data)
{
	*j = 0;
	while ((already_destroyed_or_done)[*j] != (pid_t)0)
	{
		if ((already_destroyed_or_done)[*j] == (*data).pids[*i])
			return (1);
		(*j)++;
	}
	return (0);
}

void	destroy_all(t_data *data, pid_t ret_pid,
		pid_t	*already_destroyed_or_done)
{
	int	i;
	int	j;
	int	check_done;

	j = 0;
	while ((already_destroyed_or_done)[j] != (pid_t)0
			&& j < (*data).n_of_philos)
		j++;
	(already_destroyed_or_done)[j] = ret_pid;
	i = 0;
	while (i < (*data).n_of_philos)
	{
		check_done = check_if_done(&i, &j, already_destroyed_or_done, data);
		if (!check_done)
		{
			(already_destroyed_or_done)[j] = (*data).pids[i];
			kill((*data).pids[i], SIGKILL);
		}
		i++;
	}
	sem_close(data->stop_sem);
}
// printf("\n\nreturn kill %d \n\n", kill(data->pids[i], SIGQUIT));