// #include "asm_op.h"
#include "asm.h"
// #include "libft/libft.h"

int		ft_contains(char *str, t_label label)
{
	t_l *tmp;

	tmp = label.start;
	// //printf("%s\n", str);
	while (tmp != NULL)
	{
		// //printf("hey1\n");
		if (ft_strcmp(tmp->name, str) == 0)
		{
			// //printf("hey2\n");
			return (1);
		}
		tmp = tmp->next;
		// //printf("hey2\n");
	}
	return (0);
}

void	find_label(t_champ *champ)
{
	int i;
	char *str;
	int sum;

	sum = 0;
	if (champ->labels[champ->l_size].arg_now == 1)
	{
		// //printf("1\n");
		str = champ->labels[champ->l_size].l_name_1;
		// //printf("%s\n", champ->labels[champ->l_size].l_name_1);
	}
	else if (champ->labels[champ->l_size].arg_now == 2)
	{
		// //printf("2\n");
		str = champ->labels[champ->l_size].l_name_2;
	}
	else if (champ->labels[champ->l_size].arg_now == 3)
	{
		// //printf("3\n");
		str = champ->labels[champ->l_size].l_name_3;
	}
	i = 0;
	// //printf("%s - STR\n", str);
	while (i != champ->l_size)
	{
		if (champ->labels[i].is_label == 1 && ft_contains(str, champ->labels[i]) /*ft_strcmp(str, champ->labels[i].name) == 0*/)
		{
			while (i != champ->l_size)
			{
				sum -= champ->labels[i].arg_1 + champ->labels[i].arg_2 + champ->labels[i].arg_3 + 1 +\
				champ->labels[i].cmd_type;
				i++;
			}
			break ;
		}
		i++;
	}
	if (champ->labels[champ->l_size].arg_now == 1)
	{
		champ->labels[champ->l_size].range_1 = sum;
	}
	else if (champ->labels[champ->l_size].arg_now == 2)
	{
		champ->labels[champ->l_size].range_2 = sum;
	}
	else if (champ->labels[champ->l_size].arg_now == 3)
	{
		champ->labels[champ->l_size].range_3 = sum;
	}
}

int		find_label_after_cmd(t_champ *champ, char *l_name, int start, int arg)
{
	int i;
	int sum;

	i = start;
	sum = 0;
	while (i < champ->l_size + 1)
	{
	    // //printf("z1");
		if (ft_contains(l_name, champ->labels[i]))
        {
            // //printf("z2");
            break;
        }
		sum += champ->labels[i].arg_1 + champ->labels[i].arg_2 + champ->labels[i].arg_3 + 1 +\
				champ->labels[i].cmd_type;
		i++;
		if (i == champ->l_size + 1)
			return (0);
	}
	if (arg == 1)
		champ->labels[start].range_1 = sum;
	else if (arg == 2)
		champ->labels[start].range_2 = sum;
	else if (arg == 3)
		champ->labels[start].range_3 = sum;
	return (1);
}