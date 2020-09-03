/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:29:31 by damerica          #+#    #+#             */
/*   Updated: 2019/09/18 22:30:04 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_write_str(char *newstr, char const *s, int i, int i1)
{
	int i2;

	i2 = 0;
	while (i != i1 + 1)
	{
		newstr[i2] = s[i];
		i2++;
		i++;
	}
	newstr[i2] = '\0';
	return (newstr);
}
