/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_comment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 13:51:12 by damerica          #+#    #+#             */
/*   Updated: 2020/09/23 13:51:13 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_comment(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == COMMENT_CHAR || line[i] == ALT_COMMENT)
		return (1);
	else if (line[i] == '\0')
		return (1);
	return (0);
}

void	skip_spaces(int i, char *line)
{
	while (line[i] != '\0')
	{
		if (line[i] == COMMENT_CHAR || line[i] == ALT_COMMENT)
			break ;
		if (line[i] != ' ' && line[i] != '\t')
		{
			exit(-1);
		}
		i++;
	}
}

void	while_in_m_comment(t_champ *champ, char **line, int *i, int *j)
{
	int ans;

	if (*j >= COMMENT_LENGTH)
		free_all(*champ);
	else if ((*line)[*i] == '\0')
	{
		free(*line);
		champ->comment[(*j)++] = '\n';
		while ((ans = get_next_line(champ->fd, line)) > 0)
		{
			*i = 0;
			if ((*line)[0] == '\0')
				champ->comment[(*j)++] = '\n';
			else
				break ;
		}
		if (ans <= 0)
			free_all(*champ);
	}
}

void	init_main_com(int *j, int *len_const, int *i, char **line)
{
	*j = 0;
	*len_const = ft_strlen(COMMENT_CMD_STRING);
	*i = 0;
	while ((*line)[*i] == ' ' || (*line)[*i] == '\t')
		(*i)++;
}

int		is_main_comment(char **line, int fd, t_champ *champ, int mc)
{
	int len_const;
	int i;
	int j;

	init_main_com(&j, &len_const, &i, line);
	if (ft_strncmp(COMMENT_CMD_STRING, &(*line)[i], len_const))
		return (0);
	i = len_const;
	if (mc == 1)
		free_all(*champ);
	while ((*line)[i] != '"' && (*line)[i] != '\0' &&\
	(*line)[i] != COMMENT_CHAR && (*line)[i] != ALT_COMMENT)
		i++;
	if ((*line)[i++] != '"')
		free_all(*champ);
	champ->fd = fd;
	while ((*line)[i] != '"')
	{
		while_in_m_comment(champ, line, &i, &j);
		if ((*line)[i] == '"')
			break ;
		champ->comment[j++] = (*line)[i++];
	}
	skip_spaces(i + 1, *line);
	return (1);
}
