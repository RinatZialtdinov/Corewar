/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 17:01:56 by damerica          #+#    #+#             */
/*   Updated: 2019/10/17 21:21:57 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	int		i;
	char	*str1;

	str1 = (char *)str;
	i = 0;
	while (str1[i] != '\0')
	{
		if (str1[i] == ch)
		{
			return (&str1[i]);
		}
		i++;
	}
	if (str1[i] == ch)
	{
		return (&str1[i]);
	}
	return (NULL);
}
