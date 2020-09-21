/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 16:06:18 by damerica          #+#    #+#             */
/*   Updated: 2019/10/18 22:22:29 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*buff;
	size_t	start;
	size_t	end;
	size_t	i;

	if (s == NULL)
		return (NULL);
	start = 0;
	while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		start++;
	end = start;
	while (s[end] != '\0')
		end++;
	if (end > start)
		end--;
	while ((s[end] == ' ' || s[end] == '\n' || s[end] == '\t'))
		end--;
	if (!(buff = malloc(end - start + 2)))
		return (NULL);
	i = 0;
	while (start <= end)
		buff[i++] = s[start++];
	buff[i] = '\0';
	return (buff);
}
