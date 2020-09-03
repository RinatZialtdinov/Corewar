/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 13:15:58 by damerica          #+#    #+#             */
/*   Updated: 2019/09/18 18:04:48 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 == *s2)
	{
		s1 = s1 + 1;
		s2 = s2 + 1;
		n = n - 1;
		if ((*s1 == '\0' && *s2 == '\0') || (n == 0))
			return (0);
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
