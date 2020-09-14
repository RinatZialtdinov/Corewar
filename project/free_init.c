// #include "asm_op.h"
#include "asm.h"
// #include "libft/libft.h"

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

void	free_all(t_champ champ)
{
	int i;

	i = 0;
	while (i < champ.l_size + 1)
	{
		free_label(champ.labels[i]);
		i++;
	}
	free(champ.labels);
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
		champ->labels[i].arg_1 = 0;
		champ->labels[i].arg_2 = 0;
		champ->labels[i].arg_3 = 0;
		champ->labels[i].type_1 = 0;
		champ->labels[i].type_2 = 0;
		champ->labels[i].type_3 = 0;
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
		i++;
	}
}

void	increase_array(t_champ *champ)
{
	int i;
	int j;

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
			while (j != 256)
			{
				// champ->labels[i].name[j] = '\0';
				champ->labels[i].l_name_1[j] = '\0';
				champ->labels[i].l_name_2[j] = '\0';
				champ->labels[i].l_name_3[j] = '\0';
				j++;
			}
			j = 0;
			while (j != 6)
			{
				champ->labels[i].cmd_name[j] = '\0';
			}
			champ->labels[i].is_label = 0;
			champ->labels[i].cmd_type = 0;
			champ->labels[i].range_1 = 0;
			champ->labels[i].range_2 = 0;
			champ->labels[i].range_3 = 0;
			champ->labels[i].arg_now = 0;
			i++;
		}
	}
	champ->l_size++;
}

void	zero_exec(t_champ *champ, int exec_size)
{
	int i;

	i = 0;
	while (i < exec_size)
		champ->exec_code[i++] = 0;
}