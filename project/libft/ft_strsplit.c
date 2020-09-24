/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 16:21:14 by damerica          #+#    #+#             */
/*   Updated: 2019/09/18 20:57:02 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	char	**new;
	int		count;
	int		i1;
	int		i;
	int		j;

	i = -1;
	i1 = -1;
	if (!s || !(new = (char **)malloc(sizeof(char *) * \
		((count = ft_ft_nword(s, c)) + 1))))
		return (NULL);
	while (s[++i] != '\0')
	{
		if (s[i] != c)
		{
			j = 0;
			while (s[i] != c && s[++i] != '\0')
				j++;
			if (!(new[++i1] = (char *)malloc(sizeof(char) * (j + 1))))
				return (NULL);
		}
		if (s[i] == '\0')
			break ;
	}
	return (ft_nwrite_str(count, s, c, new));
}
