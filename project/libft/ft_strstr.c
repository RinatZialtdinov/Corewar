/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 18:51:47 by damerica          #+#    #+#             */
/*   Updated: 2019/09/18 18:55:59 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str1, const char *to_find)
{
	int		j;
	int		k;
	char	*str;

	str = (char *)str1;
	k = 0;
	j = 0;
	if (!to_find[j])
		return (str);
	while (*str != '\0')
	{
		while (to_find[j] != '\0' && *str == to_find[j])
		{
			j = j + 1;
			k = k + 1;
			str = str + 1;
		}
		if (to_find[j] == '\0')
		{
			return (&str[(k - j) - k]);
		}
		str = str - j + 1;
		j = 0;
	}
	return (NULL);
}
