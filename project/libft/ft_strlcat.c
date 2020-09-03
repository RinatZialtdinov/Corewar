/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 19:58:53 by damerica          #+#    #+#             */
/*   Updated: 2019/09/18 18:05:27 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	int i;
	int j;
	int k;

	i = 0;
	j = ft_strlen(dest);
	k = ft_strlen(src);
	if ((int)size <= j)
		return (k + size);
	while ((dest[i] != '\0') && i < ((int)size - 1))
		i++;
	while (*src && i < ((int)size - 1))
	{
		dest[i] = *src;
		i++;
		src++;
	}
	dest[i] = '\0';
	return (j + k);
}
