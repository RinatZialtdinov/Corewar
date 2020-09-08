/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 15:20:56 by damerica          #+#    #+#             */
/*   Updated: 2020/09/01 15:20:58 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_op.h"
#include "asm.h"
#include "op.h"
#include <stdlib.h>
#include "libft/libft.h"
#include <fcntl.h>

int	is_comment(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == COMMENT_CHAR)
		return (1);
	else if (line[i] == '\0')
		return (1);
	return (0);
}

void	skip_spaces(int i, char *line)
{
	//printf("%c\n", line[i]);
	while(line[i] != '\0')
	{
		if (line[i] == COMMENT_CHAR)
			break ;
		if (line[i] != ' ' || line[i] != '\t')
		{
			//error невалидная строка
			printf("невалидная строка\n");
			exit(0);
		}
		i++;
	}
}

int	is_main_comment(char **line, int fd, t_champ *champ, int mc)
{
	int len_const;
	int i;
	int j;

	j = 0;
	len_const = ft_strlen(COMMENT_CMD_STRING);
	i = 0;
	while ((*line)[i] == ' ' || (*line)[i] == '\t')
		i++;	
	if (ft_strncmp(COMMENT_CMD_STRING, &(*line)[i], len_const))
	{
		return (0);
	}
	i = len_const;
	if (mc == 1)
	{
		//error	два комментария
		printf("два комментария\n");
		exit(0);
	}
	while ((*line)[i] != '"' && (*line)[i] != '\0' && (*line)[i] != COMMENT_CHAR)
		i++;
	if ((*line)[i] != '"')
	{
		//error не нашли имя
		printf("не нашли имя\n");
		exit(0);
	}
	i++;
	while ((*line)[i] != '"')
	{
		champ->comment[j] = (*line)[i];
		i++;
		j++;
		if (j > COMMENT_LENGTH)
		{
			//error длинное имя
			printf("длинное имя\n");
			exit(0);
		}
		else if ((*line)[i] == '\0')
		{
			free(*line);
			if ((len_const = get_next_line(fd, line)) > 0)
			{
				i = 0;
			}
			else
			{
				//error неполный файл или невалидный
				printf("неполный файл или невалидный\n");
				exit(0);
			}
		}
	}
	//printf("hey\n");
	skip_spaces(i + 1, *line);
	return (1);
}

// char	*trim_start_line(char *line)
// {
// 	int i;

// 	i = 0;
// 	while (line[i] == ' ' || line[i] == '\t')
// 		i++;
// 	return (&line[i]);
// }

int	is_name(char **line, int fd, t_champ *champ, int name)
{
	int len_const;
	int i;
	int j;

	j = 0;
	len_const = ft_strlen(NAME_CMD_STRING);
	i = 0;
	while ((*line)[i] == ' ' || (*line)[i] == '\t')
		i++;	
	if (ft_strncmp(NAME_CMD_STRING, &(*line)[i], len_const))
	{
		return (0);
	}
	if (name)
	{
		//error  два имени
		printf("два имени\n");
		exit(0);
	}
	i = len_const;
	while ((*line)[i] != '"' && (*line)[i] != '\0' && (*line)[i] != COMMENT_CHAR)
		i++;
	if ((*line)[i] != '"')
	{
		//error не нашли имя
		printf("не нашли имя\n");
		exit(0);
	}
	i++;
	while ((*line)[i] != '"')
	{
		champ->name[j] = (*line)[i];
		i++;
		j++;
		if (j > PROG_NAME_LENGTH)
		{
			//error длинное имя
			printf("длинное имя\n");
			exit (0);
		}
		else if ((*line)[i] == '\0')
		{
			free(*line);
			if ((len_const = get_next_line(fd, line)) > 0)
			{
				i = 0;
			}
			else
			{
				//error неполный файл или невалидный
				printf("неполный файл или невалидный\n");
				exit(0);
			}
		}
	}
	skip_spaces(i + 1, *line);
	return (1);
}

void is_header_valid(int fd, t_champ *champ)
{
	int name;
	int mc;
	char *line;
	int ans;

	name = 0;
	mc = 0;
	while ((ans = get_next_line(fd, &line)) > 0)
	{
		if (is_comment(line))
			;
		else if (is_name(&line, fd, champ, name))
			name = 1;
		else if (is_main_comment(&line, fd, champ, mc))
			mc = 1;
		free(line);
		if (name == 1 && mc == 1)
			break ;
	}
}

char	*check_name_com(char *line, t_champ *champ)
{
	int end;
	int i;
	int j;
	char *result;

	i = 0;
	// printf("%c_sd_s___\n", line[i]);
	while (line[i] == ' ' && line[i] == '\t')
	{
		i++;
	}
	end = i;
	i = 0;
	j = i;
	while (line[j] != ' ' && line[j] != '\t' && line[j] != '\0' && line[j] != COMMENT_CHAR)
		j++;
	// printf("%c________!!!!_________________\n", line[end]);
	while (i != 16 && ft_strncmp(&line[end], g_op[i].name, j - end) != 0)
	{
		i++;
	}
	if (i != 16)
	{
		result = ft_strsub(line, end, end + (j - end));
		champ->labels[champ->l_size].cmd_code = g_op[i].code;
		return (result);
	}
	//printf("s\n");
	return (NULL);
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

int		char_in_label(char el)
{
	int i;

	i = 0;
	while (LABEL_CHARS[i] != '\0')
	{
		if (LABEL_CHARS[i] == el)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

// void	add_range(t_champ *champ)
// {
// 	int i;
// 	int sum;
// 	int copy;

// 	i = 0;
// 	sum = 0;
// 	copy = champ->new_com;
// 	while (copy != champ->l_size)
// 	{
// 		sum += champ->labels[copy].range;
// 		copy++;
// 	}
// 	copy = champ->new_com;
// 	while (champ->new_com != champ->l_size)
// 	{
// 		champ->labels[champ->new_com].range = sum;
// 		champ->new_com++;
// 	}
// 	while (i != copy)
// 	{
// 		champ->labels[i].range += champ->labels[copy].range;
// 		i++;
// 	}
// }

int		ft_contains(char *str, t_label label)
{
	t_l *tmp;

	tmp = label.start;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, str) == 0)
			return (1);
		tmp = tmp->next;
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
		str = champ->labels[champ->l_size].l_name_1;
	}
	else if (champ->labels[champ->l_size].arg_now == 2)
	{
		str = champ->labels[champ->l_size].l_name_2;
	}
	else if (champ->labels[champ->l_size].arg_now == 3)
	{
		str = champ->labels[champ->l_size].l_name_3;
	}
	i = 0;
	printf("%s - STR\n", str);
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
			champ->labels[champ->l_size].arg_1++; //add
		else if (g_op[k].args_num - count_arg + 1 == 2)
			champ->labels[champ->l_size].arg_2++;
		else if (g_op[k].args_num - count_arg + 1 == 3)
			champ->labels[champ->l_size].arg_3++;
		i++;
		while (line[i] >= '0' && line[i] <= '9')
		{
			i++;
		}
		if (ft_atoi(&line[1]) > REG_NUMBER || i == 1)
		{
			// error Невалидный аргумент
			exit(0);
		}
	}
	else if (line[i] == DIRECT_CHAR)
	{
		if (g_op[k].args_num - count_arg + 1 == 1)
			champ->labels[champ->l_size].arg_1 += g_op[k].t_dir_size; //add
		else if (g_op[k].args_num - count_arg + 1 == 2)
			champ->labels[champ->l_size].arg_2 += g_op[k].t_dir_size;
		else if (g_op[k].args_num - count_arg + 1 == 3)
			champ->labels[champ->l_size].arg_3 += g_op[k].t_dir_size;
		i++;
		if (line[i] == LABEL_CHAR)
		{
			i++;
			while (char_in_label(line[i]))
			{
				//printf("ifowhfisdhofhsdoifhsdofhsdofhosdhfosdhfosdhfosd|_________________________________|||||\n");
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
			if (line[i] != ',' && line[i] != '\t' && line[i] != '\0')
			{
				//error не тот символ
				printf("не тот символ\n");
				exit (0);
			}

			find_label(champ); // написать!!!!!!!!
			
			//increase_array(champ);//champ->l_size++;
			 // add____`
			//add_range(champ);
		}
		else if ((line[i] >= '0' && line[i] <= '9') || line[i] == '-')
		{
			if (line[i] == '-')
				i++;
			while (line[i] >= '0' && line[i] <= '9')
			{
				i++;
			}
			if (line[i - 1] == '-' || i == 1)
			{
				// error Невалидный аргумент
				printf("Невалидный аргумент\n");
				exit(0);
			}
		}
	}
	else if (line[i] == '-' || (line[i] >= '0' && line[i] <= '9'))
	{
		if (line[i] == '-')
			i++;
		if (g_op[k].args_num - count_arg + 1 == 1)
			champ->labels[champ->l_size].arg_1 += 2; 
		else if (g_op[k].args_num - count_arg + 1 == 2)
			champ->labels[champ->l_size].arg_2 += 2;
		else if (g_op[k].args_num - count_arg + 1 == 3)
			champ->labels[champ->l_size].arg_3 += 2;

		while (line[i] >= '0' && line[i] <= '9')
			i++;
		if (line[i - 1] == '-' && i == 1)
		{
			// error Невалидный аргумент2
			printf("Невалидный аргумент2\n");
			exit(0);
		}
	}
	else if (line[i] == LABEL_CHAR)
	{
		if (g_op[k].args_num - count_arg + 1 == 1)
			champ->labels[champ->l_size].arg_1 += 2; 
		else if (g_op[k].args_num - count_arg + 1 == 2)
			champ->labels[champ->l_size].arg_2 += 2;
		else if (g_op[k].args_num - count_arg + 1 == 3)
			champ->labels[champ->l_size].arg_3 += 2;
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
				printf("не тот символ2\n");
				exit (0);
			}
			
			find_label(champ);
			
			//increase_array(champ);//champ->l_size++; //add____`
			// add_range(champ);
	}
	return (i);
}

void	convert_command(char *line, t_champ *champ)
{
	int i;
	int count_arg;
	i = 0;
//printf("line[i] - %c\n", line[0]);
	while (ft_strcmp(g_op[i].name, champ->labels[champ->l_size].cmd_name) != 0)
	{
		i++;
	}
	count_arg = g_op[i].args_num;
	
	
	if (g_op[i].args_types_code)
		champ->labels[champ->l_size].cmd_type = 1;
	else
	{
		champ->labels[champ->l_size].cmd_type = 0;
	} // fix it esli nado
	



	i = 0;
	int comma = 0;
	champ->new_com = champ->l_size;
	while (line[i] != '\0')
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == 'r' || line[i] == DIRECT_CHAR || line[i] == '-' || line[i] == LABEL_CHAR || (line[i] >= '0' && line[i] <= '9'))
		{
			if (comma == 1)
			{
				// error	Нет запятой
				printf("Нет запятой");
				exit(0);
			}
			comma = 1;
			//printf("ya tut %c\n", line[i]);
			i += switch_args(&line[i], count_arg, champ);
			//printf("%c --------- %d\n", line[i], comma);
			count_arg--;
		}
		else if (line[i] == SEPARATOR_CHAR)
		{
			if (comma == 0)
			{
				// error	Лишняя запятая
				printf("Лишняя запятая");
				exit(0);
			}
			comma = 0;
			i++;
		}
		else if (line[i] == COMMENT_CHAR)
		{
			if (count_arg != 0)
			{
				//error не все аргументы были найдены
				//printf("не все аргументы были найдены");
				exit(0);
			}
			increase_array(champ);
			return ;
		}
		else if (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
		{
			//error non-valid symbol
			printf("%s - LINE, %c - SYMBOL non-valid symbol\n", line, line[i]);
			exit(0);
		}
		
	}
	if (comma == 0 || count_arg != 0)
	{
		// error	Лишняя запятая или не все аргументы были найдены
		printf("Лишняя запятая или не все аргументы были найдены");
		exit(0);
	}
	// champ->l_size++; // add____`
	//add_range(champ);
	increase_array(champ);
}

int	is_command(char *line, t_champ *champ)
{
	int i;
	char *name_com;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	//printf("fsdf\n");
	name_com = check_name_com(&line[i], champ);
	//printf("fsdf2\n");
	if (name_com == NULL)
	{//printf("fsdf3\n");
		return (0);
	}
	// printf("sdsdsd\n");
	ft_strcpy(champ->labels[champ->l_size].cmd_name, name_com);
	// for (int q = 0; q < ft_strlen(name_com); q++) {
		// champ->labels[champ->l_size].cmd_name[q] = name_com[q];
	// }
	//printf("%s _____________________\n", name_com);
	free(name_com);
	convert_command(&line[i + ft_strlen(name_com) + 1], champ);
	return (1);
}

int		is_label(char *line, t_champ *champ)
{
	int i;
	int len;
	t_l *new;

	i = 0;
	//printf("HEY\n");
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	len = i;
	while (line[i] != ' ' && line[i] != '\t' && line[i] != LABEL_CHAR &&\
	line[i] != '\0' && line[i] != COMMENT_CHAR)
		i++;
	if (line[i] == LABEL_CHAR)
	{
		champ->labels[champ->l_size].is_label = 1;
		if (champ->labels[champ->l_size].names == NULL)
		{
			//printf("hey\n");
			new = malloc(sizeof(t_l));
			ft_strncpy(new->name, &line[len], i - len);
			new->name[i - len] = '\0';
			// printf("%s - name\n", new->name);
			//printf("hey\n");
			new->next = NULL;
			champ->labels[champ->l_size].names = new;
			//printf("%s - LABEL\n", champ->labels[champ->l_size].names->name);
			champ->labels[champ->l_size].start = new;
		}
		else
		{
			new = malloc(sizeof(t_l));
			ft_strncpy(new->name, &line[len], i - len);
			new->name[i - len] = '\0';
			new->next = NULL;
			champ->labels[champ->l_size].names->next = new;
			champ->labels[champ->l_size].names = new;
		}
		
	}
	else
	{
		return (0);
	}
	i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	printf("%c _!_!_\n", line[i]);
	if (line[i] == '\0'|| line[i] == COMMENT_CHAR)
		return (1);
	else if (is_command(&line[i], champ))
	{
		return (1);
	}
	else
	{
		//error
		printf("если это не команда\n");
		exit(0);
	}
}

int		find_label_after_cmd(t_champ *champ, char *l_name, int start, int arg)
{
	int i;
	int sum;

	i = start;
	sum = 0;
	while (i < champ->l_size)
	{
		sum += champ->labels[i].arg_1 + champ->labels[i].arg_2 + champ->labels[i].arg_3 + 1 +\
				champ->labels[i].cmd_type;
		if (ft_contains(l_name, champ->labels[i]))
			break ;
		i++;
		if (i == champ->l_size)
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

void	finish_fill_label_range(t_champ *champ)
{
	int i;

	i = 0;
	while (i < champ->l_size)
	{
		if (champ->labels[i].l_name_1[0] && champ->labels[i].range_1 == 0)
		{
			if (find_label_after_cmd(champ, champ->labels[i].l_name_1, i, 1))
				;
			else
			{
				/* else Не нашел метку */
				printf("Не нашел метку1\n");
				exit(0);
			}
		}
		if (champ->labels[i].l_name_2[0] && champ->labels[i].range_2 == 0)
		{
			if (find_label_after_cmd(champ, champ->labels[i].l_name_2, i, 2))
				;
			else
			{
				/* else Не нашел метку */
				printf("Не нашел метку2 %s\n", champ->labels[i].l_name_2);
				exit(0);
			}
		}
		if (champ->labels[i].l_name_3[0] && champ->labels[i].range_3 == 0)
		{
			if (find_label_after_cmd(champ, champ->labels[i].l_name_3, i, 3))
				;
			else
			{
				/* else Не нашел метку */
				printf("Не нашел метку3\n");
				exit(0);
			}
		}
		i++;
	}
}

void	is_body_valid(int fd, t_champ *champ)
{
	int ans;
	char *line;

	while ((ans = get_next_line(fd, &line)) > 0)
	{
		//printf("%s\n", line);
		if (is_comment(line))
			;
		else if (is_command(line, champ))
			;
		else if (is_label(line, champ))
			;
		else
		{
			// ERROR nevalidnyi vvod
			printf("nevalidnyi vvod\n");
			exit(0);
		}
		free(line);
	}
	finish_fill_label_range(champ);
}

void	is_file_valid(char *name, t_champ *champ)
{
	int len;
	int fd;

	len = ft_strlen(name);
	if (len > 2 && name[len - 2] == '.' && name[len - 1] == 's')
	{
		fd = open(name, O_RDONLY);
		if (fd > 0)
		{
			is_header_valid(fd, champ);
			is_body_valid(fd, champ);
		}
	}
	else
	{
		//error неправильное название файла
		//printf("неправильное название файла\n");
		exit (0);
	}
	close(fd);
}

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
	while (i < champ.l_size)
	{
		free_label(champ.labels[i]);
		i++;
	}
	free(champ.labels);
}

char	*change_extension(char *filename, char *old, char *new)
{
	char	*basename;

	basename = ft_strsub(filename, 0, ft_strlen(filename) - ft_strlen(old));
	if (!basename)
	{
		//error
		exit(0);
	}
	if (!(filename = ft_strjoin(basename, new)))
	{
		//error
		exit(0);
	}
	ft_strdel(&basename);
	return (filename);
}

int		count_code_size(t_champ *champ)
{

	return 0;
}

void	to_bin_code(t_champ *champ)
{
	champ->code_size = count_code_size(champ);

	champ->exec_code = malloc(sizeof(char) * (16 + PROG_NAME_LENGTH + COMMENT_LENGTH + champ->code_size));
}

int	main(int argc, char **argv)
{
	t_champ champ;
	int fd;

	init_array(&champ);
	if (argc != 2)
	{
		// error.  неверное кол-во файлов
		return (0);
	}
	else
	{
		is_file_valid(argv[1], &champ);
	}
	//to_bin_code(&champ);
	char *file_name = change_extension(argv[1], ".s", ".cor");
	fd = open(file_name, O_CREAT|O_WRONLY|O_TRUNC, 0777);
	printf("\n\n\n");
	printf("%s - NAME\n", champ.name);
	printf("%s - COMMENT\n", champ.comment);
	for (int i = 0; i < champ.l_size; i++)
	{
		printf("%s - CMD_NAME, %x - CMD_CODE, %s - NAME_LABEL, %d - ARG_1, %d - ARG_2, %d - ARG_3, %d - CMD_TYPE, %s - L_NAME_1,  %s - L_NAME_2, %d - RANGE_1, %d - RANGE_2, %d - RANGE_3\n", champ.labels[i].cmd_name, \
						champ.labels[i].cmd_code ,champ.labels[i].names->name, champ.labels[i].arg_1, champ.labels[i].arg_2, champ.labels[i].arg_3, \
						champ.labels[i].cmd_type, champ.labels[i].l_name_1, champ.labels[i].l_name_2, champ.labels[i].range_1, champ.labels[i].range_2, champ.labels[i].range_3);
	}
	printf("fdsafa\n");
	free_all(champ);
	return (0);
}
