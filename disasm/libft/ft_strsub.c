/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:45:43 by damerica          #+#    #+#             */
/*   Updated: 2019/10/17 21:23:47 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*frstr;
	int		i;
	int		count;

	if (!s)
		return (NULL);
	count = 0;
	i = 0;
	frstr = (char *)malloc(sizeof(char) * (len + 1));
	if (!frstr)
		return (NULL);
	while (s[i] != '\0')
		i++;
	i = (int)start;
	while (count != (int)len)
	{
		frstr[count] = s[i];
		count++;
		i++;
	}
	frstr[count] = '\0';
	return (frstr);
}
