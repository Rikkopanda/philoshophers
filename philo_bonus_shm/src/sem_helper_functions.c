/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_helper_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rik <rik@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:57:38 by rik               #+#    #+#             */
/*   Updated: 2024/01/15 14:56:34 by rik              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	make_semaphore(char **sem_name_ptr, char nbr_str[1000], char *name)
{
	char	philo_name_str[1000];

	philo_name_str[0] = '\0';
	ft_strcpy(philo_name_str, name);
	ft_strcat(philo_name_str, nbr_str);
	*sem_name_ptr = ft_strdup(philo_name_str);
}

void	open_named_semaphore(sem_t **sem_ptr, char **sem_name_ptr, int value)
{
	sem_unlink(*sem_name_ptr);
	*sem_ptr = sem_open(*sem_name_ptr, O_CREAT, 0644, value);
	if (*sem_ptr == SEM_FAILED)
		perror("sem_open\n");
}
