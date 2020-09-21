/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:23:09 by damerica          #+#    #+#             */
/*   Updated: 2019/09/18 17:55:02 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *b, size_t lenght)
{
	int i;

	i = 0;
	while (lenght != 0)
	{
		((char *)b)[i] = '\0';
		i++;
		lenght--;
	}
}
