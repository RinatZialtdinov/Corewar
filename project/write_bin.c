/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:26:33 by damerica          #+#    #+#             */
/*   Updated: 2020/09/23 12:26:34 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_bin_head(t_champ *champ)
{
	int i;

	i = 0;
	write_4_byte(champ, (unsigned int)COREWAR_EXEC_MAGIC);
	while (champ->name[i])
	{
		champ->exec_code[champ->ind_wr++] = champ->name[i++];
	}
	champ->ind_wr = PROG_NAME_LENGTH + 8;
	write_4_byte(champ, (unsigned int)champ->code_size);
	i = 0;
	while (champ->comment[i])
	{
		champ->exec_code[champ->ind_wr++] = champ->comment[i++];
	}
	champ->ind_wr = PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
}

void	process_args(t_champ *champ, int i)
{
	if (champ->labels[i].arg_1 == 1)
		write_1_byte(champ, champ->labels[i].range_1);
	else if (champ->labels[i].arg_1 == 2)
		write_2_byte(champ, champ->labels[i].range_1);
	else if (champ->labels[i].arg_1 == 4)
		write_4_byte(champ, champ->labels[i].range_1);
	if (champ->labels[i].arg_2 == 1)
		write_1_byte(champ, champ->labels[i].range_2);
	else if (champ->labels[i].arg_2 == 2)
		write_2_byte(champ, champ->labels[i].range_2);
	else if (champ->labels[i].arg_2 == 4)
	{
		write_4_byte(champ, champ->labels[i].range_2);
	}
	if (champ->labels[i].arg_3 == 1)
		write_1_byte(champ, champ->labels[i].range_3);
	else if (champ->labels[i].arg_3 == 2)
		write_2_byte(champ, champ->labels[i].range_3);
	else if (champ->labels[i].arg_3 == 4)
		write_4_byte(champ, champ->labels[i].range_3);
}

void	write_exec_code(t_champ *champ)
{
	int i;

	i = 0;
	while (i < champ->l_size)
	{
		champ->exec_code[champ->ind_wr++] = champ->labels[i].cmd_code;
		if (champ->labels[i].cmd_type == 1)
			champ->exec_code[champ->ind_wr++] = count_code_type_arg(champ, i);
		process_args(champ, i);
		i++;
	}
}

void	to_bin_code(t_champ *champ, int fd)
{
	int i;
	int exec_size;

	i = 0;
	champ->code_size = count_code_size(champ);
	exec_size = 16 + PROG_NAME_LENGTH + COMMENT_LENGTH + champ->code_size;
	champ->exec_code = malloc(sizeof(char) * (exec_size));
	zero_exec(champ, exec_size);
	champ->ind_wr = 0;
	write_bin_head(champ);
	write_exec_code(champ);
	write(fd, champ->exec_code, exec_size);
	i = 0;
}
