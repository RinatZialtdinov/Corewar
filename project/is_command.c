// #include "asm_op.h"
#include "asm.h"
// #include "libft/libft.h"

void	convert_command(char *line, t_champ *champ)
{
	int i;
	int count_arg;
	i = 0;
////printf("line[i] - %c\n", line[0]);
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
	}
	



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
				//printf("Нет запятой");
				free_all(*champ);
				exit(-1);
			}
			comma = 1;
			////printf("ya tut %c\n", line[i]);
			i += switch_args(&line[i], count_arg, champ);
			////printf("%c --------- %d\n", line[i], comma);
			count_arg--;
		}
		else if (line[i] == SEPARATOR_CHAR)
		{
			if (comma == 0)
			{
				// error	Лишняя запятая
				//printf("Лишняя запятая");
				free_all(*champ);
				exit(-1);
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
				exit(-1);
			}
			increase_array(champ);
			return ;
		}
		else if (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
		{
			//error non-valid symbol
			//printf("non-valid symbol, %s\n", line);
			free_all(*champ);
			exit(-1);
		}
		
	}
	if (comma == 0 || count_arg != 0)
	{
		// error	Лишняя запятая или не все аргументы были найдены
		//printf("Лишняя запятая или не все аргументы были найдены");
		free_all(*champ);
		exit(-1);
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
	// //printf("hey1_is command\n");
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	////printf("fsdf\n");
	name_com = check_name_com(&line[i], champ);
	////printf("fsdf2\n");
	if (name_com == NULL || line[i + ft_strlen(name_com)] == LABEL_CHAR)
	{////printf("fsdf3\n");
		return (0);
	}
	// //printf("sdsdsd\n");
	ft_strcpy(champ->labels[champ->l_size].cmd_name, name_com);
	// for (int q = 0; q < ft_strlen(name_com); q++) {
		// champ->labels[champ->l_size].cmd_name[q] = name_com[q];
	// }
	////printf("%s _____________________\n", name_com);
	free(name_com);
	convert_command(&line[i + ft_strlen(name_com)], champ);
	// //printf("hey2_is command\n");
	return (1);
}