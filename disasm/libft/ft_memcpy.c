/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:29:05 by damerica          #+#    #+#             */
/*   Updated: 2019/09/18 17:55:43 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *source, size_t count)
{
	int i;

	i = 0;
	while (count != 0 && (dest || source))
	{
		((unsigned char *)dest)[i] = ((unsigned char *)source)[i];
		i++;
		count--;
	}
	return (dest);
}
