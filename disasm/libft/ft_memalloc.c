/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 14:41:44 by damerica          #+#    #+#             */
/*   Updated: 2019/09/18 18:15:23 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*a;
	int		i;

	i = 0;
	a = malloc(sizeof(size_t) * size);
	if (!a)
		return (NULL);
	while (size != 0)
	{
		a[i] = '\0';
		i++;
		size--;
	}
	return (a);
}
