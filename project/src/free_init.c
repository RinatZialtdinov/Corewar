/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:25:15 by damerica          #+#    #+#             */
/*   Updated: 2020/09/23 12:25:18 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_label(t_label label)
{
	t_l *to_del;
	t_l *tmp;

	to_del = label.start;
	while (to_del)
	{
		tmp = to_del->next;
		free(to_del);
		to_del = tmp;
	}
}

void	free_all(t_champ champ, char *str)
{
	int i;

	i = 0;
	while (i < champ.l_size + 1)
	{
		free_label(champ.labels[i]);
		i++;
	}
	free(champ.labels);
	if (str)
	{
		write(0, str, ft_strlen(str));
		exit(-1);
	}
	exit(0);
}

void	zeroing_values(t_champ *champ, int i, int j)
{
	while (j != 256)
	{
		champ->labels[i].l_name_1[j] = '\0';
		champ->labels[i].l_name_2[j] = '\0';
		champ->labels[i].l_name_3[j] = '\0';
		j++;
	}
	j = 0;
	while (j != 6)
	{
		champ->labels[i].cmd_name[j] = '\0';
		j++;
	}
	champ->labels[i].is_label = 0;
	champ->labels[i].cmd_type = 0;
	champ->labels[i].range_1 = 0;
	champ->labels[i].range_2 = 0;
	champ->labels[i].range_3 = 0;
	champ->labels[i].arg_now = 0;
}

void	init_array(t_champ *champ)
{
	int i;
	int j;

	j = 0;
	i = 0;
	champ->l_size = 0;
	champ->labels = malloc(sizeof(t_label) * 250);
	while (i != 250)
	{
		champ->labels[i].names = NULL;
		champ->labels[i].start = NULL;
		champ->labels[i].arg_1 = 0;
		champ->labels[i].arg_2 = 0;
		champ->labels[i].arg_3 = 0;
		champ->labels[i].arg_now = 0;
		champ->labels[i].type_1 = 0;
		champ->labels[i].type_2 = 0;
		champ->labels[i].type_3 = 0;
		zeroing_values(champ, i, j);
		i++;
	}
}

void	increase_array(t_champ *champ)
{
	int i;
	int j;

	j = 0;
	if ((champ->l_size + 1) % 250 == 0)
	{
		champ->labels = realloc(champ->labels, champ->l_size + 251);
		i = champ->l_size + 1;
		champ->labels[i].names = NULL;
		while (i != 250 + champ->l_size)
		{
			champ->labels[i].arg_1 = 0;
			champ->labels[i].arg_2 = 0;
			champ->labels[i].arg_3 = 0;
			zeroing_values(champ, i, j);
			i++;
		}
	}
	champ->l_size++;
}
