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
			//printf("невалидная строка\n");
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
		//printf("два комментария\n");
		exit(0);
	}
	while ((*line)[i] != '"' && (*line)[i] != '\0' && (*line)[i] != COMMENT_CHAR)
		i++;
	if ((*line)[i] != '"')
	{
		//error не нашли имя
		//printf("не нашли имя\n");
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
			//printf("длинное имя\n");
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
				//printf("неполный файл или невалидный\n");
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
		//printf("два имени\n");
		exit(0);
	}
	i = len_const;
	while ((*line)[i] != '"' && (*line)[i] != '\0' && (*line)[i] != COMMENT_CHAR)
		i++;
	if ((*line)[i] != '"')
	{
		//error не нашли имя
		//printf("не нашли имя\n");
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
			//printf("длинное имя\n");
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
				//printf("неполный файл или невалидный\n");
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

char	*check_name_com(char *line)
{
	int end;
	int i;
	int j;
	char *result;

	i = 0;
	// //printf("%c_sd_s___", line[i]);
	while (line[i] == ' ' && line[i] == '\t')
	{
		i++;
	}
	end = i;
	i = 0;
	j = i;
	while (line[j] != ' ' && line[j] != '\t')
		j++;
	//printf("%c_________________________\n", line[end]);
	while (ft_strncmp(&line[end], g_op[i].name, j - end) != 0 && i != 16)
	{
		i++;
	}
	if (i != 16)
	{
		result = ft_strsub(line, end, end + (j - end));
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
		champ->labels[i].arg_1 = 0;
		champ->labels[i].arg_2 = 0;
		champ->labels[i].arg_3 = 0;
		while (j != 256)
		{
			champ->labels[i].name[j] = '\0';
			j++;
		}
		j = 0;
		while (j != 6)
		{
			champ->labels[i].cmd_name[j] = '\0';
		}
		champ->labels[i].is_label = 0;
		champ->labels[i].cmd_type = 0;
		champ->labels[i].range = 0;
		i++;
	}
}

void	increase_array(t_champ *champ)
{
	int i;

	i = 0;
	if ((champ->l_size + 1) % 50 == 0)
	{
		champ->labels = realloc(champ->labels, champ->l_size + 51);
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

void	add_range(t_champ *champ)
{
	int i;
	int sum;
	int copy;

	i = 0;
	sum = 0;
	copy = champ->new_com;
	while (copy != champ->l_size)
	{
		sum += champ->labels[copy].range;
		copy++;
	}
	copy = champ->new_com;
	while (champ->new_com != champ->l_size)
	{
		champ->labels[champ->new_com].range = sum;
		champ->new_com++;
	}
	while (i != copy)
	{
		champ->labels[i].range += champ->labels[copy].range;
		i++;
	}
}

int	switch_args(char *line, int count_arg, t_champ *champ, char *name_com)
{
	int i;
	int j;
	int k;

	k = 0;
	j = 0;
	// init_array(champ);
	i = 0;
	while (ft_strcmp(g_op[k].name, name_com) != 0)
	{
		k++;
	}
	//increase_array(champ); // add____`
	if (line[i] == 'r')
	{
		champ->labels[champ->l_size].range++; //add
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
		champ->labels[champ->l_size].range += g_op[k].t_dir_size;
		i++;
		if (line[i] == LABEL_CHAR)
		{
			i++;
			while (char_in_label(line[i]))
			{
				//printf("ifowhfisdhofhsdoifhsdofhsdofhosdhfosdhfosdhfosd|_________________________________|||||\n");
				champ->labels[champ->l_size].name[j] = line[i];
				j++;
				i++;
			}
			if (line[i] != ',' && line[i] != '\t' && line[i] != '\0')
			{
				//error не тот символ
				exit (0);
			}
			increase_array(champ);//champ->l_size++;
			 // add____`
			//add_range(champ);
		}
		else if (line[i] >= '0' && line[i] <= '9')
		{
			while (line[i] >= '0' && line[i] <= '9')
			{
				i++;
			}
			if (i == 1)
			{
				// error Невалидный аргумент
				exit(0);
			}
		}
	}
	else if (line[i] == '-' || (line[i] >= '0' && line[i] <= '9'))
	{
		champ->labels[champ->l_size].range += 2; // add
		while (line[i] == '-' || (line[i] >= '0' && line[i] <= '9'))
			i++;
	}
	else if (line[i] == LABEL_CHAR)
	{
		champ->labels[champ->l_size].range += 2; // add
		i++;
			while (char_in_label(line[i]))
			{
				champ->labels[champ->l_size].name[j] = line[i];
				j++;
				i++;
			}
			if (line[i] != ',' && line[i] != '\t' && line[i] != '\0')
			{
				//error не тот символ
				exit (0);
			}
			increase_array(champ);//champ->l_size++; //add____`
			// add_range(champ);
	}
	return (i);
}

void	convert_command(char *line, char *name_com, t_champ *champ)
{
	int i;
	int count_arg;
	i = 0;
//printf("line[i] - %c\n", line[0]);
	while (ft_strcmp(g_op[i].name, name_com) != 0)
	{
		i++;
	}
	count_arg = g_op[i].args_num;
	
	
	if (g_op[i].args_types_code)
		champ->labels[champ->l_size].range = 2;
	else
	{
		champ->labels[champ->l_size].range = 1;
	} // fix it esli nado
	



	i = 0;
	int comma = 0;
	champ->new_com = champ->l_size;
	while (line[i] != '\0')
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == 'r' || line[i] == DIRECT_CHAR || line[i] == LABEL_CHAR || (line[i] >= '0' && line[i] <= '9'))
		{
			if (comma == 1)
			{
				// error	Нет запятой
				//printf("Нет запятой");
				exit(0);
			}
			comma = 1;
			//printf("ya tut %c\n", line[i]);
			i += switch_args(&line[i], count_arg, champ, name_com);
			//printf("%c --------- %d\n", line[i], comma);
			count_arg--;
		}
		if (line[i] == SEPARATOR_CHAR)
		{
			if (comma == 0)
			{
				// error	Лишняя запятая
				//printf("Лишняя запятая");
				exit(0);
			}
			comma = 0;
			i++;
		}
		if (line[i] == COMMENT_CHAR)
		{
			if (count_arg != 0)
			{
				//error не все аргументы были найдены
				//printf("не все аргументы были найдены");
				exit(0);
			}
			return ;
		}
	}
	if (comma == 0 || count_arg != 0)
	{
		// error	Лишняя запятая или не все аргументы были найдены
				//printf("Лишняя запятая или не все аргументы были найдены");
		exit(0);
	}
	// champ->l_size++; // add____`
	add_range(champ);
}

int	is_command(char **line, t_champ *champ)
{
	int i;
	char *name_com;

	i = 0;
	while ((*line)[i] == ' ' || (*line)[i] == '\t')
		i++;
	name_com = check_name_com(&(*line)[i]);
	if (name_com == NULL)
	{
		return (0);
	}
	//printf("%s _____________________\n", name_com);
	convert_command(&(*line)[i + ft_strlen(name_com) + 1], name_com, champ);
	return (1);
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
		else if (is_command(&line, champ))
			;
		// else if (is_label(&line))
		//printf("hey\n");
		// 	;
	}
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
}

int	main(int argc, char **argv)
{
	t_champ champ;

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
	printf("\n\n\n");
	printf("%s - NAME\n", champ.name);
	printf("%s - COMMENT\n", champ.comment);
	for (int i = 0; i < champ.l_size; i++)
	{
		printf("%s - LNAME, %d - RANGE\n", champ.labels[i].name, champ.labels[i].range);
	}
	//printf("fdsafa\n");
	return (0);
}
