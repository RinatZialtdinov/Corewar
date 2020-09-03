/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:46:56 by damerica          #+#    #+#             */
/*   Updated: 2019/09/18 22:44:13 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buffer, int ch, size_t count)
{
	unsigned char	*str;
	int				k;

	k = 0;
	str = (unsigned char *)buffer;
	while ((int)count != k)
	{
		if ((unsigned char)str[k] == (unsigned char)ch)
			return (&str[k]);
		k++;
	}
	return (NULL);
}
