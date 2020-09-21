/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 18:14:35 by damerica          #+#    #+#             */
/*   Updated: 2019/09/18 18:03:06 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *str1, const char *str2, size_t count)
{
	int i;
	int j;

	i = 0;
	while (str1[i] != '\0')
	{
		i++;
	}
	j = 0;
	while (str2[j] != '\0' && count != 0)
	{
		str1[i] = str2[j];
		j++;
		i++;
		count--;
	}
	str1[i] = '\0';
	return (str1);
}
