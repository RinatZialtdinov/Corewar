/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:26:16 by damerica          #+#    #+#             */
/*   Updated: 2020/09/23 12:26:17 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	switch_args(char *line, int count_arg, t_champ *champ)
{
	int i;
	int j;
	int k;

	k = 0;
	j = 0;
	// init_array(champ);
	i = 0;
	while (ft_strcmp(g_op[k].name, champ->labels[champ->l_size].cmd_name) != 0)
	{
		k++;
	}
	//increase_array(champ); // add____`
	if (line[i] == 'r')
	{
		if (g_op[k].args_num - count_arg + 1 == 1)
		{
			champ->labels[champ->l_size].arg_1++;
			champ->labels[champ->l_size].type_1 = 1; //add
			champ->labels[champ->l_size].range_1 = get_reg_arg_val(champ, line, &i);
		}
		else if (g_op[k].args_num - count_arg + 1 == 2)
		{
			champ->labels[champ->l_size].arg_2++;
			champ->labels[champ->l_size].type_2 = 1;
			champ->labels[champ->l_size].range_2 = get_reg_arg_val(champ, line, &i);
		}
		else if (g_op[k].args_num - count_arg + 1 == 3)
		{
			champ->labels[champ->l_size].arg_3++;
			champ->labels[champ->l_size].type_3 = 1;
			champ->labels[champ->l_size].range_3 = get_reg_arg_val(champ, line, &i);
		}
		
	}
	else if (line[i] == DIRECT_CHAR)
	{
		if (g_op[k].args_num - count_arg + 1 == 1)
		{
			champ->labels[champ->l_size].arg_1 += g_op[k].t_dir_size; //add
			champ->labels[champ->l_size].type_1 = 2;
		}
		else if (g_op[k].args_num - count_arg + 1 == 2)
		{
			champ->labels[champ->l_size].arg_2 += g_op[k].t_dir_size;
			champ->labels[champ->l_size].type_2 = 2;
		}
		else if (g_op[k].args_num - count_arg + 1 == 3)
		{
			champ->labels[champ->l_size].arg_3 += g_op[k].t_dir_size;
			champ->labels[champ->l_size].type_3 = 2;
		}
		i++;
		if (line[i] == LABEL_CHAR)
		{
			i++;
			while (char_in_label(line[i]))
			{
				////printf("ifowhfisdhofhsdoifhsdofhsdofhosdhfosdhfosdhfosd|_________________________________|||||\n");
				if (g_op[k].args_num - count_arg + 1 == 1)
				{
					champ->labels[champ->l_size].arg_now = 1;
					champ->labels[champ->l_size].l_name_1[j] = line[i]; //add
				}
				else if (g_op[k].args_num - count_arg + 1 == 2)
				{
					champ->labels[champ->l_size].arg_now = 2;
					champ->labels[champ->l_size].l_name_2[j] = line[i];
				}
				else if (g_op[k].args_num - count_arg + 1 == 3)
				{
					champ->labels[champ->l_size].arg_now = 3;
					champ->labels[champ->l_size].l_name_3[j] = line[i];
				}
				// champ->labels[champ->l_size].l_name_1[j] = line[i];
				j++;
				i++;
			}
			champ->labels[champ->l_size].l_name_1[j] = '\0';
			champ->labels[champ->l_size].l_name_2[j] = '\0';
			champ->labels[champ->l_size].l_name_3[j] = '\0';
			if (line[i] != ' ' && line[i] != ',' && line[i] != '\t' && line[i] != '\0' && line[i] != COMMENT_CHAR)
			{
				//error не тот символ
				//printf("не тот символ11, %s |%c|\n", line, line[i]);
				free_all(*champ);
				exit (0);
			}

			find_label(champ); // написать!!!!!!!!
			
			//increase_array(champ);//champ->l_size++;
			 // add____`
			//add_range(champ);
		}
		else if ((line[i] >= '0' && line[i] <= '9') || line[i] == '-')
		{
			// if (line[i] == '-')
			// 	i++;
			// while (line[i] >= '0' && line[i] <= '9')
			// {
			// 	i++;
			// }
			// if (line[i - 1] == '-' || i == 1)
			// {
			// 	// error Невалидный аргумент
			// 	//printf("Невалидный аргумент\n");
			// 	exit(-1);
			// }
			if (g_op[k].args_num - count_arg + 1 == 1)
				champ->labels[champ->l_size].range_1 = get_dir_ind_arg_val(champ, line, &i);
			else if (g_op[k].args_num - count_arg + 1 == 2)
				champ->labels[champ->l_size].range_2 = get_dir_ind_arg_val(champ, line, &i);
			else if (g_op[k].args_num - count_arg + 1 == 3)
				champ->labels[champ->l_size].range_3 = get_dir_ind_arg_val(champ, line, &i);
		}
		else
		{
			//error
			//printf("не валидный аргумент\n");
			free_all(*champ);
			exit(-1);
		}
		
	}
	else if (line[i] == '-' || (line[i] >= '0' && line[i] <= '9'))
	{
		if (g_op[k].args_num - count_arg + 1 == 1)
		{
			champ->labels[champ->l_size].arg_1 += 2;
			champ->labels[champ->l_size].range_1 = get_dir_ind_arg_val(champ, line, &i);
			champ->labels[champ->l_size].type_1 = T_IND;
		} 
		else if (g_op[k].args_num - count_arg + 1 == 2)
		{
			champ->labels[champ->l_size].arg_2 += 2;
			champ->labels[champ->l_size].range_2 = get_dir_ind_arg_val(champ, line, &i);
			champ->labels[champ->l_size].type_2 = T_IND;
		}
		else if (g_op[k].args_num - count_arg + 1 == 3)
		{
			champ->labels[champ->l_size].arg_3 += 2;
			champ->labels[champ->l_size].range_3 = get_dir_ind_arg_val(champ, line, &i);
			champ->labels[champ->l_size].type_3 = T_IND;
		}
		// if (line[i] == '-')
		// 	i++;
		// while (line[i] >= '0' && line[i] <= '9')
		// 	i++;
		// if (line[i - 1] == '-' && i == 1)
		// {
		// 	// error Невалидный аргумент2
		// 	//printf("Невалидный аргумент2\n");
		// 	exit(-1);
		// }
	}
	else if (line[i] == LABEL_CHAR)
	{
		if (g_op[k].args_num - count_arg + 1 == 1)
		{
			champ->labels[champ->l_size].arg_1 += 2;
			champ->labels[champ->l_size].type_1 = T_IND; 
		}
		else if (g_op[k].args_num - count_arg + 1 == 2)
		{
			champ->labels[champ->l_size].arg_2 += 2;
			champ->labels[champ->l_size].type_2 = T_IND;
		}
		else if (g_op[k].args_num - count_arg + 1 == 3)
		{
			champ->labels[champ->l_size].arg_3 += 2;
			champ->labels[champ->l_size].type_3 = T_IND;
		}
		// champ->labels[champ->l_size].range += 2; // add
		i++;
			while (char_in_label(line[i]))
			{
				if (g_op[k].args_num - count_arg + 1 == 1)
				{
					champ->labels[champ->l_size].arg_now = 1;
					champ->labels[champ->l_size].l_name_1[j] = line[i]; //add
				}
				else if (g_op[k].args_num - count_arg + 1 == 2)
				{
					champ->labels[champ->l_size].arg_now = 2;
					champ->labels[champ->l_size].l_name_2[j] = line[i];
				}
				else if (g_op[k].args_num - count_arg + 1 == 3)
				{
					champ->labels[champ->l_size].arg_now = 3;
					champ->labels[champ->l_size].l_name_3[j] = line[i];
				}
				j++;
				i++;
			}
			champ->labels[champ->l_size].l_name_1[j] = '\0';
			champ->labels[champ->l_size].l_name_2[j] = '\0';
			champ->labels[champ->l_size].l_name_3[j] = '\0';
			if (line[i] != ',' && line[i] != '\t' && line[i] != '\0')
			{
				//error не тот символ2
				//printf("не тот символ2\n");
				free_all(*champ);
				exit (0);
			}
			
			find_label(champ);
			
			//increase_array(champ);//champ->l_size++; //add____`
			// add_range(champ);
	}
	return (i);
}
