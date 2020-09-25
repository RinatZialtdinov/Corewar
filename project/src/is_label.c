/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_label.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:25:48 by damerica          #+#    #+#             */
/*   Updated: 2020/09/23 12:25:51 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	if_in_is_label(t_champ *champ, t_l *new, char *line, int i)
{
	champ->labels[champ->l_size].is_label = 1;
	if (champ->labels[champ->l_size].names == NULL)
	{
		new = malloc(sizeof(t_l));
		ft_strncpy(new->name, &line[champ->len], i - champ->len);
		new->name[i - champ->len] = '\0';
		new->next = NULL;
		champ->labels[champ->l_size].names = new;
		champ->labels[champ->l_size].start = new;
	}
	else
	{
		new = malloc(sizeof(t_l));
		ft_strncpy(new->name, &line[champ->len], i - champ->len);
		new->name[i - champ->len] = '\0';
		new->next = NULL;
		champ->labels[champ->l_size].names->next = new;
		champ->labels[champ->l_size].names = new;
	}
}

void	init_is_label(int *i, t_champ *champ, char *line)
{
	*i = 0;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	champ->len = *i;
}

int		is_label(char *line, t_champ *champ)
{
	int i;
	t_l *new;

	new = NULL;
	init_is_label(&i, champ, line);
	while (line[i] != ' ' && line[i] != '\t' && line[i] != LABEL_CHAR && \
	line[i] != '\0' && line[i] != COMMENT_CHAR && line[i] != ALT_COMMENT &&\
	char_in_label(line[i]))
		i++;
	if (line[i] == LABEL_CHAR)
		if_in_is_label(champ, new, line, i);
	else
		return (0);
	i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i] == COMMENT_CHAR || line[i] == ALT_COMMENT)
		return (1);
	else if (is_command(&line[i], champ))
		return (1);
	else
		free_all(*champ, "Error: invalid file\n");
	return (1);
}
