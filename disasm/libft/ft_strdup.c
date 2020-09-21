/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:59:40 by damerica          #+#    #+#             */
/*   Updated: 2019/09/18 17:58:14 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*a;
	int		i;

	i = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	a = (char*)malloc(sizeof(char) * (i + 1));
	if (!a)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		a[i] = src[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}
