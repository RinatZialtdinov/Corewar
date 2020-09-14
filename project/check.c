#include "asm.h"

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
	while (line[j] != ' ' && line[j] != '\t' && line[j] != '\0' && line[j] != COMMENT_CHAR\
		&& line[j] != LABEL_CHAR && line[j] != DIRECT_CHAR)
		j++;
	// printf("%c________!!!!_________________\n", line[end]);
	if (j == end)
	{
		return (NULL);
	}
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

void	finish_fill_label_range(t_champ *champ)
{
	int i;

	i = 0;
	while (i < champ->l_size + 1)
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
				// sum_range(champ, champ->labels[i].l_name_1, 1, i);
			}
		}
		if (champ->labels[i].l_name_2[0] && champ->labels[i].range_2 == 0)
		{
			if (find_label_after_cmd(champ, champ->labels[i].l_name_2, i, 2))
				;
			else
			{
				//  else Не нашел метку */
				printf("Не нашел метку2 %s\n", champ->labels[i].l_name_2);
				//sum_range(champ, champ->labels[i].l_name_2, 2, i);
				// champ->labels[i].range_2 = 153;
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
				// sum_range(champ, champ->labels[i].l_name_3, 3, i);
			}
		}
		i++;
	}
}

void	check_type_arg(t_champ  *champ)
{
	int i;
	int j;

	i = 0;
	while (i != champ->l_size)
	{
		j = 0;
		while (ft_strcmp(g_op[j].name, champ->labels[i].cmd_name) != 0)
		{
			j++;
		}
		if ((g_op[j].args_types[0] & champ->labels[i].type_1) == 0)
		{
			//error
			printf("error1, %s\n", g_op[j].name);
			free_all(*champ);
			exit(0);
		}
		if ((g_op[j].args_types[1] & champ->labels[i].type_2) == 0  \
		&& (g_op[j].args_types[1] || champ->labels[i].type_2))
		{
			//error
			printf("error2, %s\n", g_op[j].name);
			free_all(*champ);
			exit(0);
		}
		if ((g_op[j].args_types[2] & champ->labels[i].type_3) == 0  \
		&& (g_op[j].args_types[2] || champ->labels[i].type_3))
		{
			//error
			printf("error3, %d, %d\n", g_op[j].args_types[2], champ->labels[i].type_3);
			free_all(*champ);
			exit(0);
		}
		i++;
	}
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