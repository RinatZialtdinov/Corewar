/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:46:10 by damerica          #+#    #+#             */
/*   Updated: 2019/09/18 20:50:17 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *to_find, size_t len)
{
	int		j;
	int		k;
	char	*str;

	str = (char *)str1;
	k = 0;
	j = 0;
	if (!to_find[j])
		return (str);
	while (*str != '\0' && len != 0)
	{
		while (to_find[j] != '\0' && *str == to_find[j] && len-- != 0)
		{
			j = j + 1;
			k = k + 1;
			str = str + 1;
		}
		if (to_find[j] == '\0')
			return (&str[(k - j) - k]);
		str = str - j + 1;
		len = len + j - 1;
		j = 0;
	}
	return (NULL);
}
