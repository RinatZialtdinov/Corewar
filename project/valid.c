/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:26:24 by damerica          #+#    #+#             */
/*   Updated: 2020/09/23 12:26:26 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	is_header_valid(int fd, t_champ *champ)
{
	int		name;
	int		mc;
	char	*line;
	int		ans;

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
		if (name == 1 && mc == 1)
		{
			free(line);
			break ;
		}
		if (is_command_or_not(line, champ))
			free_all(*champ);
		free(line);
	}
}

void	is_end_comment(t_champ *champ, char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '#' || line[i] == '\0')
		champ->is_end_comment = 1;
	else
		champ->is_end_comment = 0;
}

void	is_body_valid(int fd, t_champ *champ)
{
	int		ans;
	char	*line;

	while ((ans = get_next_line(fd, &line)) > 0)
	{
		if (is_comment(line))
			;
		else if (is_command(line, champ))
			;
		else if (is_label(line, champ))
			;
		else
		{
			free_all(*champ);
		}
		is_end_comment(champ, line);
		free(line);
	}
	finish_fill_label_range(champ);
}

void	is_file_valid(char *name, t_champ *champ)
{
	int		len;
	int		fd;
	int		is_ok_to_end;
	char	buff[2000000];
	int		length;

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
		exit(0);
	close(fd);
	fd = open(name, O_RDONLY);
	is_ok_to_end = 0;
	length = read(fd, &buff, 2000000);
	if (!(buff[length] == '\0' && buff[length - 1] == '\n') &&\
	!champ->is_end_comment)
		exit(-1);
}
