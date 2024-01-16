/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:33:42 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/14 13:33:44 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	min;
	int	num;

	num = 0;
	min = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t'
		|| str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '-')
		min = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + ((char)str[i] - 48);
		i++;
	}
	return (num * min);
}

static size_t	unbr_len(unsigned int n)
{
	size_t	i;

	i = 1;
	while (n / 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	ft_utoa_1000(unsigned int num, char str[1000])
{
	size_t				digits;
	int					digits_save;

	digits = unbr_len(num);
	digits_save = digits;
	(str)[digits] = '\0';
	while (digits--)
	{
		(str)[digits] = num % 10 + '0';
		num = num / 10;
	}
	return (digits_save);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
