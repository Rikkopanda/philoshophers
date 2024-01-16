/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:34:20 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/14 18:24:34 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philos;

	if (init_args_data(&data, argc, argv) == -1)
		return (-1);
	if (create_philos(&philos, &data) == -1)
		return (-1);
	join_philos(philos, data.n_of_philos);
}
