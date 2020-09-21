/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:00:10 by damerica          #+#    #+#             */
/*   Updated: 2019/09/18 18:16:15 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*a;
	int		i;

	i = 0;
	a = (char *)malloc(sizeof(char) * (size + 1));
	if (!a)
		return (NULL);
	while (size != 0)
	{
		a[i] = '\0';
		i++;
		size--;
	}
	a[i] = '\0';
	return (a);
}
