/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 18:22:17 by damerica          #+#    #+#             */
/*   Updated: 2019/09/18 17:58:38 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	int i;
	int k;

	k = n;
	i = 0;
	while (src[i] != '\0' && i != (int)n)
	{
		dest[i] = src[i];
		i = i + 1;
		k = k - 1;
	}
	if (k != 0)
		while (k != 0)
		{
			dest[i] = '\0';
			k = k - 1;
			i = i + 1;
		}
	return (dest);
}
