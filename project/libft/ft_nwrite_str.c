/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nwrite_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:43:33 by damerica          #+#    #+#             */
/*   Updated: 2019/09/18 19:50:47 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_nwrite_str(int count, char const *s, char c, char **new)
{
	int i;
	int j;
	int i1;

	i = 0;
	j = 0;
	while (j != count)
	{
		i1 = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			new[j][i1] = s[i];
			i++;
			i1++;
		}
		new[j][i1] = '\0';
		j++;
	}
	new[j] = NULL;
	return (new);
}
