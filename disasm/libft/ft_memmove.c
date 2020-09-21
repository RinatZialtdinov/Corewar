/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:42:22 by damerica          #+#    #+#             */
/*   Updated: 2019/09/18 19:25:29 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	char	*dest;
	char	*source;
	size_t	i;

	dest = (char *)s1;
	source = (char *)s2;
	if (!s1 && !s2)
		return (NULL);
	i = -1;
	if (source < dest)
	{
		while ((int)(--n) >= 0)
		{
			dest[n] = source[n];
		}
	}
	else
	{
		while (++i < n)
		{
			dest[i] = source[i];
		}
	}
	return (dest);
}
