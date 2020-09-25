/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:25:35 by damerica          #+#    #+#             */
/*   Updated: 2020/09/23 12:25:37 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		if_in_conv_com(char **line, t_champ *champ, int *i, t_tw *arg)
{
	if ((*line)[*i] == 'r' || (*line)[*i] == DIRECT_CHAR || (*line)[*i] == '-'\
	|| (*line)[*i] == LABEL_CHAR || ((*line)[*i] >= '0' && (*line)[*i] <= '9'))
	{
		if (arg->comma == 1)
			free_all(*champ, "Error: no comma\n");
		arg->comma = 1;
		*i += switch_args(&((*line)[*i]), arg->count_arg, champ);
		arg->count_arg--;
	}
	else if ((*line)[(*i)++] == SEPARATOR_CHAR)
	{
		if (arg->comma == 0)
			free_all(*champ, "Error: extra comma\n");
		arg->comma = 0;
	}
	else if ((*line)[--(*i)] == COMMENT_CHAR || (*line)[*i] == ALT_COMMENT)
	{
		if (arg->count_arg != 0)
			exit(-1);
		increase_array(champ);
		return (1);
	}
	else if ((*line)[*i] != ' ' && (*line)[*i] != '\t' && (*line)[*i] != '\0')
		free_all(*champ, "Error: invalid symbol\n");
	return (0);
}

void	convert_command(char *line, t_champ *champ)
{
	int		i;
	t_tw	arg;

	i = 0;
	while (ft_strcmp(g_op[i].name, champ->labels[champ->l_size].cmd_name) != 0)
		i++;
	arg.count_arg = g_op[i].args_num;
	if (g_op[i].args_types_code)
		champ->labels[champ->l_size].cmd_type = 1;
	else
		champ->labels[champ->l_size].cmd_type = 0;
	i = 0;
	arg.comma = 0;
	champ->new_com = champ->l_size;
	while (line[i] != '\0')
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (if_in_conv_com(&line, champ, &i, &arg))
			return ;
	}
	if (arg.comma == 0 || arg.count_arg != 0)
		free_all(*champ, "Error: Extra comma or not all args were found\n");
	increase_array(champ);
}

int		is_command(char *line, t_champ *champ)
{
	int		i;
	char	*name_com;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	name_com = check_name_com(&line[i], champ);
	if (name_com == NULL || line[i + ft_strlen(name_com)] == LABEL_CHAR)
	{
		free(name_com);
		return (0);
	}
	ft_strcpy(champ->labels[champ->l_size].cmd_name, name_com);
	free(name_com);
	convert_command(&line[i + ft_strlen(name_com)], champ);
	return (1);
}
