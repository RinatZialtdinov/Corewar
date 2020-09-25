/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:12:32 by damerica          #+#    #+#             */
/*   Updated: 2020/09/25 16:33:26 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "asm.h"

// char		*change_extension(char *filename, char *old, char *new)
// {
// 	char	*basename;
// 	int		len;

// 	len = ft_strlen(filename);
// 	if (len < 5 && ft_strcmp(&filename[len - 5], ".cor") != 0)
// 	{
// 		write(1, "Wrong extansion\n", 16);
// 		exit(-1);
// 	}
// 	basename = ft_strsub(filename, 0, ft_strlen(filename) - ft_strlen(old));
// 	if (!basename)
// 	{
// 		exit(-1);
// 	}
// 	if (!(filename = ft_strjoin(basename, new)))
// 	{
// 		exit(-1);
// 	}
// 	ft_strdel(&basename);
// 	return (filename);
// }

// void		write_head_elem(char *elem, int cons, int wr_fd, int rd_fd)
// {
// 	char	c;
// 	int		i;

// 	write(wr_fd, elem, ft_strlen(elem));
// 	i = 0;
// 	read(rd_fd, &c, 1);
// 	while (c != '\0' && i++ < cons)
// 	{
// 		write(wr_fd, &c, 1);
// 		read(rd_fd, &c, 1);
// 	}
// 	write(wr_fd, "\"\n", 2);
// 	while (i++ < cons)
// 		read(rd_fd, &c, 1);
// }

// void		disasm_header(int wr_fd, int rd_fd)
// {
// 	char	c;
// 	int		i;

// 	i = 0;
// 	while (i++ < 4)
// 		read(rd_fd, &c, 1);
// 	write_head_elem(".name \"", PROG_NAME_LENGTH, wr_fd, rd_fd);
// 	i = 0;
// 	while (i++ < 7)
// 		read(rd_fd, &c, 1);
// 	write_head_elem(".comment \"", COMMENT_LENGTH, wr_fd, rd_fd);
// 	write(wr_fd, "\n", 1);
// 	i = 0;
// 	while (i++ < 3)
// 		read(rd_fd, &c, 1);
// }

static int	ft_numlen(int n, int minus)
{
	int numlen;

	numlen = 1;
	while ((n /= 10))
		numlen++;
	return (numlen + minus);
}

char		*ft_itoa_1(int n)
{
	char	*str;
	int		numlen;
	int		minus;
	int		digit;

	minus = (n < 0) ? 1 : 0;
	numlen = ft_numlen(n, minus);
	if ((str = ft_strnew((size_t)numlen)))
	{
		str[numlen--] = '\0';
		while (numlen >= minus)
		{
			digit = n % 10;
			str[numlen--] = (char)((digit < 0 ? -digit : digit) + '0');
			n /= 10;
		}
		if (minus)
			str[0] = '-';
	}
	return (str);
}

// char		*find_cmd(t_dis *dis)
// {
// 	int i;

// 	i = 0;
// 	while (i < 16)
// 	{
// 		if (g_op[i].code == dis->c)
// 			break ;
// 		i++;
// 	}
// 	dis->arg_type = (int)g_op[i].args_types_code;
// 	dis->cmd_name = g_op[i].name;
// 	dis->dir_size = g_op[i].t_dir_size;
// 	return (g_op[i].name);
// }

// void		check_arg_type(t_dis *dis, int rd_fd)
// {
// 	int i;

// 	i = 0;
// 	if (dis->arg_type == 1)
// 	{
// 		read(rd_fd, &dis->c, 1);
// 		dis->arg1 = dis->c >> 6;
// 		dis->arg2 = dis->c >> 4 & 3;
// 		dis->arg3 = dis->c >> 2 & 3;
// 	}
// 	else
// 	{
// 		while (i < 16)
// 		{
// 			if (g_op[i].code == dis->c)
// 				break ;
// 			i++;
// 		}
// 		dis->arg1 = g_op[i].args_types[0];
// 	}
// }

// void		write_arg(int wr_fd, t_dis *dis, int rd_fd, int arg)
// {
// 	char	*to_wr;
// 	int		output;
// 	char	p;

// 	dis->value = 0;
// 	if (arg == 1)
// 	{
// 		write(wr_fd, "r", 1);
// 		read(rd_fd, &dis->c, 1);
// 		output = dis->c;
// 	}
// 	else if (arg == 2)
// 	{
// 		p = DIRECT_CHAR;
// 		write(wr_fd, "%", 1);
// 		if (dis->dir_size == 2)
// 		{
// 			read(rd_fd, &dis->c, 1);
// 			dis->value = dis->c;
// 			dis->value = dis->value << 8;
// 			read(rd_fd, &dis->c, 1);
// 			dis->value = dis->value | dis->c;
// 			output = (int16_t)dis->value;
// 		}
// 		else if (dis->dir_size == 4)
// 		{
// 			read(rd_fd, &dis->c, 1);
// 			dis->value = dis->c;
// 			dis->value = dis->value << 8;
// 			read(rd_fd, &dis->c, 1);
// 			dis->value = dis->value | dis->c;

// 			dis->value = dis->value << 8;
// 			read(rd_fd, &dis->c, 1);
// 			dis->value = dis->value | dis->c;

// 			dis->value = dis->value << 8;
// 			read(rd_fd, &dis->c, 1);
// 			dis->value = dis->value | dis->c;
// 			output = dis->value;
// 		}
// 	}
// 	else if (arg == 3)
// 	{
// 		read(rd_fd, &dis->c, 1);
// 		dis->value = dis->c;
// 		dis->value = dis->value << 8;
// 		read(rd_fd, &dis->c, 1);
// 		dis->value = dis->value | dis->c;
// 		output = (int16_t)dis->value;
// 	}
// 	to_wr = ft_itoa_1(output);
// 	write(wr_fd, to_wr, ft_strlen(to_wr));
// 	free(to_wr);
// }

// void		disasm_cmd(int wr_fd, int rd_fd)
// {
// 	int		ans;
// 	t_dis	dis;

// 	while ((ans = read(rd_fd, &dis.c, 1)) > 0)
// 	{
// 		dis.arg1 = 0;
// 		dis.arg2 = 0;
// 		dis.arg3 = 0;
// 		write(wr_fd, find_cmd(&dis), ft_strlen(dis.cmd_name));
// 		write(wr_fd, " ", 1);
// 		check_arg_type(&dis, rd_fd);
// 		write_arg(wr_fd, &dis, rd_fd, dis.arg1);
// 		if (dis.arg2)
// 		{
// 			write(wr_fd, ", ", 2);
// 			write_arg(wr_fd, &dis, rd_fd, dis.arg2);
// 		}
// 		if (dis.arg3)
// 		{
// 			write(wr_fd, ", ", 2);
// 			write_arg(wr_fd, &dis, rd_fd, dis.arg3);
// 		}
// 		write(wr_fd, "\n", 1);
// 	}
// }

int		main(int argc, char *argv[])
{
	int		wr_fd;
	int		rd_fd;
	char	*file_name;

	if (argc != 2)
	{
		write(1, "Args more or less than 1\n", 25);
		return (0);
	}
	rd_fd = open(argv[1], O_RDONLY);
	file_name = change_extension(argv[1], ".cor", ".s");
	wr_fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	disasm_header(wr_fd, rd_fd);
	disasm_cmd(wr_fd, rd_fd);
	write(1, "Writing output program to ", 26);
	write(1, file_name, ft_strlen(file_name));
	write(1, "\n", 1);
	free(file_name);
	return (0);
}
