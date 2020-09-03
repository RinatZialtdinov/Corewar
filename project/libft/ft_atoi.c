/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:08:10 by damerica          #+#    #+#             */
/*   Updated: 2019/09/18 19:59:50 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoi(const char *str)
{
	int					z;
	unsigned long long	res;

	z = 1;
	res = 0;
	while (*str == '\n' || *str == '\t' || *str == '\v'
			|| *str == '\r' || *str == '\f' || *str == ' ')
		str = str + 1;
	if (*str == '+')
		str = str + 1;
	else if (*str == '-')
	{
		z = -1;
		str = str + 1;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = (unsigned long long)(10 * res + (*str - 48));
		str = str + 1;
	}
	if (res >= 9223372036854775807 && z == 1)
		return (-1);
	if (res >= 9223372036854775807 && z == -1)
		return (0);
	return (z * res);
}
