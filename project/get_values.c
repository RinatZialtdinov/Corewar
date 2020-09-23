/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:25:27 by damerica          #+#    #+#             */
/*   Updated: 2020/09/23 12:25:28 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	get_reg_arg_val(t_champ *champ, char *line, int *i)
{
	(*i)++;
	while (line[*i] >= '0' && line[*i] <= '9')
		(*i)++;
	if (ft_atoi(&line[1]) > REG_NUMBER || *i == 1 || ft_atoi(&line[1]) < 1)
	{
		free_all(*champ);
	}
	return (ft_atoi(&line[1]));
}

int	get_dir_ind_arg_val(t_champ *champ, char *line, int *i)
{
	int start;

	start = *i;
	if (line[*i] == '-')
		(*i)++;
	while (line[*i] >= '0' && line[*i] <= '9')
		(*i)++;
	if (line[*i - 1] == '-' && *i == 1)
	{
		free_all(*champ);
	}
	return (ft_atoi(&line[start]));
}
