/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:09:40 by damerica          #+#    #+#             */
/*   Updated: 2019/09/18 17:55:22 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buf, int ch, size_t count)
{
	int i;

	i = 0;
	while (count != 0)
	{
		((unsigned char *)buf)[i] = ch;
		i++;
		count--;
	}
	return (buf);
}
