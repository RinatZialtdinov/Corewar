/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_n_byte.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:26:39 by damerica          #+#    #+#             */
/*   Updated: 2020/09/23 12:26:40 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_4_byte(t_champ *champ, unsigned int to_write)
{
	unsigned char	buff;
	int				shift;

	shift = 24;
	while (shift >= 0)
	{
		buff = (unsigned char)((to_write >> shift));
		champ->exec_code[champ->ind_wr] = buff;
		shift -= 8;
		champ->ind_wr++;
	}
}

void	write_2_byte(t_champ *champ, unsigned int to_write)
{
	unsigned char	buff;
	int				shift;

	shift = 8;
	while (shift >= 0)
	{
		buff = (unsigned char)((to_write >> shift));
		champ->exec_code[champ->ind_wr] = buff;
		shift -= 8;
		champ->ind_wr++;
	}
}

void	write_1_byte(t_champ *champ, unsigned int to_write)
{
	champ->exec_code[champ->ind_wr++] = (unsigned char)(to_write);
}
