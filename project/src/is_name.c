/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_name.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:25:56 by damerica          #+#    #+#             */
/*   Updated: 2020/09/23 12:25:58 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	while_is_name(char **line, int *i, t_champ *champ, int *j)
{
	int ans;

	if ((*line)[(*i)++] != '"')
	{
		free(*line);
		free_all(*champ, "Error: no name\n");
	}
	while ((*line)[*i] != '"')
	{
		if (*j >= PROG_NAME_LENGTH)
		{
			free(*line);
			free_all(*champ, "Error: name is too long\n");
		}
		else if ((*line)[*i] == '\0')
		{
			free(*line);
			champ->name[(*j)++] = '\n';
			if ((ans = get_next_line(champ->fd, line)) > 0)
				*i = 0;
			else
				free_all(*champ, "Error: invalid file\n");
		}
		champ->name[(*j)++] = (*line)[(*i)++];
	}
}

int		is_name(char **line, int fd, t_champ *champ, int name)
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
		return (0);
	if (name)
	{
		free(*line);
		free_all(*champ, "Error: two or more names\n");
	}
	i += len_const;
	while ((*line)[i] != '"' && (*line)[i] != '\0' &&\
	(*line)[i] != COMMENT_CHAR && (*line)[i] != ALT_COMMENT &&\
	((*line)[i] == ' ' || (*line)[i] == '\t'))
		i++;
	champ->fd = fd;
	while_is_name(line, &i, champ, &j);
	skip_spaces(i + 1, *line, champ);
	return (1);
}

int		is_command_or_not(char *line, t_champ *champ)
{
	int		i;
	char	*name_com;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	name_com = NULL;
	name_com = check_name_com(&line[i], champ);
	if (name_com == NULL)
	{
		return (0);
	}
	free(name_com);
	return (1);
}
