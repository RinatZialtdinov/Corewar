#include "asm.h"

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
	////printf("%c\n", line[i]);
	while(line[i] != '\0')
	{
		if (line[i] == COMMENT_CHAR)
			break ;
		if (line[i] != ' ' && line[i] != '\t')
		{
			//error невалидная строка
			//printf("невалидная строка\n");
			exit(-1);
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
		free_all(*champ);
		exit(-1);
	}
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
		// //printf("hey\n");
		// champ->comment[j] = (*line)[i];
		// i++;
		// j++;
		if (j >= COMMENT_LENGTH)
		{
			//error длинное имя
			// //printf("длинный коммент\n");
			// write(0, "FD\n", 3);
			free_all(*champ);
			exit(-1);
		}
		else if ((*line)[i] == '\0')
		{
			free(*line);
			champ->comment[j] = '\n';
			j++;
			while ((len_const = get_next_line(fd, line)) > 0)
			{
				i = 0;
				if ((*line)[0] == '\0')
				{
					champ->comment[j] = '\n';
					j++;
				}
				else
				{
					break ;
				}
			}
			if (len_const <= 0)
			{
				//error неполный файл или невалидный
				//printf("неполный файл или невалидный\n");
				free_all(*champ);
				exit(-1);
			}
		}
		// i++;
		if ((*line)[i] == '"')
			break ;
		champ->comment[j] = (*line)[i];
		i++;
		j++;
		// champ->comment[j] = (*line)[i];
	}
	////printf("hey\n");
	skip_spaces(i + 1, *line);
	return (1);
}