// #include "asm_op.h"
#include "asm.h"
// #include "libft/libft.h"

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
		free_all(*champ);
		exit(-1);
	}
	i = len_const;
	while ((*line)[i] != '"' && (*line)[i] != '\0' && (*line)[i] != COMMENT_CHAR)
		i++;
	if ((*line)[i] != '"')
	{
		//error не нашли имя
		//printf("не нашли имя\n");
		free_all(*champ);
		exit(-1);
	}
	i++;
	while ((*line)[i] != '"')
	{
		if (j >= PROG_NAME_LENGTH)
		{
			//error длинное имя
			//printf("длинное имя\n");
			free_all(*champ);
			exit (0);
		}
		else if ((*line)[i] == '\0')
		{
			free(*line);
			champ->name[j] = '\n';
			j++;
			if ((len_const = get_next_line(fd, line)) > 0)
			{
				i = 0;
			}
			else
			{
				//error неполный файл или невалидный
				//printf("неполный файл или невалидный\n");
				free_all(*champ);
				exit(-1);
			}
		}
		champ->name[j] = (*line)[i];
		i++;
		j++;
	}
	skip_spaces(i + 1, *line);
	return (1);
}

int	is_command_or_not(char *line, t_champ *champ)
{
	int i;
	char *name_com;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	////printf("fsdf\n");
	name_com = NULL;
	name_com = check_name_com(&line[i], champ);
	if (name_com == NULL)
	{
		return (0);
	}
	free(name_com);
	return (1);
}