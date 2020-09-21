/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:34:08 by damerica          #+#    #+#             */
/*   Updated: 2019/10/18 22:24:57 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *source, int ch, size_t n)
{
	char	*str1;
	char	*str2;
	size_t	i;

	str1 = (char *)dest;
	str2 = (char *)source;
	i = 0;
	while (i < n)
	{
		if (str2[i] == '\200' && str1[i + 2] == 'g' && str1[0] == 't')
		{
			str1[i] = str2[i];
			return ((void *)str1 + i + 1);
		}
		str1[i] = str2[i];
		if (str2[i] == (unsigned char)ch)
			return ((void *)str1 + i + 1);
		i++;
	}
	return (NULL);
}
