/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 17:15:10 by damerica          #+#    #+#             */
/*   Updated: 2019/09/18 18:38:20 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int		i;
	char	*str1;

	str1 = (char *)str;
	i = 0;
	while (str1[i] != '\0')
	{
		i++;
	}
	while (i != -1)
	{
		if (str1[i] == ch)
		{
			return (&str1[i]);
		}
		i--;
	}
	return (NULL);
}
