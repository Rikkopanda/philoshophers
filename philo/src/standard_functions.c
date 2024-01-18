/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rik <rik@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:33:42 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/18 10:09:06 by rik              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_space(char c)
{
	if (c == ' ' || c == '\t'
		|| c == '\n' || c == '\r'
		|| c == '\f' || c == '\v')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	num;

	num = 0;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + ((char)str[i] - 48);
		i++;
	}
	return (num);
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
