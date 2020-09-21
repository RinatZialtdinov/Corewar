/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:12:32 by damerica          #+#    #+#             */
/*   Updated: 2020/09/21 13:12:34 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "asm.h"
#include "asm_op.h"

char	*change_extension(char *filename, char *old, char *new)
{
	char	*basename;
    int len;

    len = ft_strlen(filename);
    if (len < 5 && ft_strcmp(&filename[len-5], ".cor") != 0)
    {
        printf("Wrong extansion\n");
        exit(-1);
    }
	basename = ft_strsub(filename, 0, ft_strlen(filename) - ft_strlen(old));
	if (!basename)
	{
		//error
		//printf("error in change_extension\n");
		exit(-1);
	}
	if (!(filename = ft_strjoin(basename, new)))
	{
		//error
		//printf("error in change_extension\n");
		exit(-1);
	}
	ft_strdel(&basename);
	return (filename);
}

void    write_head_elem(char *elem, int cons, int wr_fd, int rd_fd)
{
    char c;
    int i;

    write(wr_fd, elem, ft_strlen(elem));
    i = 0;
    read(rd_fd, &c, 1);
    while (c != '\0' && i++ < cons)
    {
        write(wr_fd, &c, 1);
        read(rd_fd, &c, 1);
    }
    write(wr_fd, "\"\n", 2);
    while (i++ < cons)
        read(rd_fd, &c, 1);
}

void    disasm_header(int wr_fd, int rd_fd)
{
    char c;
    int i;
    
    i = 0;
    while (i++ < 4)
        read(rd_fd, &c, 1);
    write_head_elem(".name \"", PROG_NAME_LENGTH, wr_fd, rd_fd);
    i = 0;
    while (i++ < 7)
        read(rd_fd, &c, 1);
    write_head_elem(".comment \"", COMMENT_LENGTH, wr_fd, rd_fd);
    write(wr_fd, "\n", 1);
    i = 0;
    while (i++ < 3)
        read(rd_fd, &c, 1);
    // write(wr_fd, ".name \"", 7);
    // i = 0;
    // while (i++ < 5)
    //     read(rd_fd, &c, 1);
    // while (c != '\0' && i++ < PROG_NAME_LENGTH)
    // {
    //     write(wr_fd, &c, 1);
    //     read(rd_fd, &c, 1);
    // }
    // write(wr_fd, "\"\n", 2);
    // while (i < PROG_NAME_LENGTH)
    //     read(rd_fd, &c, 1);
}

typedef struct s_dis
{
    char        *cmd_name;
    unsigned int         arg_type;
    unsigned char        c;
    unsigned int         value;
    unsigned int         arg1;
    unsigned int         arg2;
    unsigned int         arg3;
    unsigned int         dir_size;
}               t_dis;

static int		ft_numlen(int n, int minus)
{
	int numlen;

	numlen = 1;
	while ((n /= 10))
		numlen++;
	return (numlen + minus);
}

char			*ft_itoa_1(int n)
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
			// str[numlen--] = (char)(FT_ABS(digit) + '0');
            str[numlen--] = (char)((digit < 0 ? -digit : digit) + '0');
			n /= 10;
		}
		if (minus)
			str[0] = '-';
	}
	return (str);
}

char    *find_cmd(t_dis *dis)
{
    int i;

    i = 0;
    printf("%d - CMDMDMD\n", dis->c);
    while (i < 16)
    {
        if (g_op[i].code == dis->c)
            break;
        i++;
    }
    dis->arg_type = (int)g_op[i].args_types_code;
    dis->cmd_name = g_op[i].name;
    dis->dir_size = g_op[i].t_dir_size;
    return (g_op[i].name);
}

void    check_arg_type(t_dis *dis, int rd_fd)
{
    int i;

    i = 0;
    if (dis->arg_type == 1)
    {
        read(rd_fd, &dis->c, 1);
        printf("ya tut - %d\n", dis->arg_type);
        dis->arg1 = dis->c >> 6;
        dis->arg2 = dis->c >> 4 & 3;
        dis->arg3 = dis->c >> 2 & 3;
    }
    else
    {
        while (i < 16)
        {
            if (g_op[i].code == dis->c)
                break;
            i++;
        }
        dis->arg1 = g_op[i].args_types[0];
    }
}



void    write_arg(int wr_fd, t_dis *dis, int rd_fd, int arg)
{
    char    *to_wr;
    int     output;
    dis->value = 0;

    if (arg == 1)
    {
        write(wr_fd, "r", 1);
        read(rd_fd, &dis->c, 1);
        output = dis->c;
    }
    else if (arg == 2)
    {
        printf("heysdadasd\n");
        char p = DIRECT_CHAR;
        write(wr_fd, "%", 1);
        if (dis->dir_size == 2)
        {
            read(rd_fd, &dis->c, 1);
            dis->value = dis->c;
            dis->value = dis->value<<8;
            read(rd_fd, &dis->c, 1);
            dis->value = dis->value | dis->c;
            output = (int16_t)dis->value;
        }
        else if (dis->dir_size == 4)
        {
            read(rd_fd, &dis->c, 1);
            dis->value = dis->c;
            dis->value = dis->value<<8;
            read(rd_fd, &dis->c, 1);
            dis->value = dis->value | dis->c;

            dis->value = dis->value<<8;
            read(rd_fd, &dis->c, 1);
            dis->value = dis->value | dis->c;

            dis->value = dis->value<<8;
            read(rd_fd, &dis->c, 1);
            dis->value = dis->value | dis->c;
            output = dis->value;
        }
    }
    else if (arg == 3)
    {
        read(rd_fd, &dis->c, 1);
        dis->value = dis->c;
        dis->value = dis->value<<8;
        read(rd_fd, &dis->c, 1);
        dis->value = dis->value | dis->c;
        output = (int16_t)dis->value;
    }
    // if (arg != 0)
    // {
    to_wr = ft_itoa_1(output);
    write(wr_fd, to_wr, ft_strlen(to_wr));
    free(to_wr);
    // }
}

void    disasm_cmd(int wr_fd, int rd_fd)
{
    int i;
    int ans;
    t_dis dis;

    i = 0;
    while ((ans = read(rd_fd, &dis.c, 1)) > 0)
    {
        dis.arg1 = 0;
        dis.arg2 = 0;
        dis.arg3 = 0;
        printf("hey\n");
        write(wr_fd, find_cmd(&dis), ft_strlen(dis.cmd_name));
        write(wr_fd, " ", 1);
        printf("hey\n");
        check_arg_type(&dis, rd_fd);
        printf("arg_type - %d\n", dis.arg_type);
        write_arg(wr_fd, &dis, rd_fd, dis.arg1);
        if (dis.arg2)
        {
            write(wr_fd, ", ", 2);
            write_arg(wr_fd, &dis, rd_fd, dis.arg2);
        }
        if (dis.arg3)
        {
            write(wr_fd, ", ", 2);
            write_arg(wr_fd, &dis, rd_fd, dis.arg3);
        }
        write(wr_fd, "\n", 1);
        // dis.arg_type = 0;
        // dis.dir_size = 0;
        // dis.value = 0;
    }
}

int main(int argc, char *argv[])
{
    int wr_fd;
    int rd_fd;

    if (argc != 2)
    {
        printf("Args more or less than 1\n");
        return (0);
    }
    rd_fd = open(argv[1], O_RDONLY);
    char *file_name = change_extension(argv[1], ".cor", ".s");
    wr_fd = open(file_name, O_CREAT|O_WRONLY|O_TRUNC, 0777);
    disasm_header(wr_fd, rd_fd);
    disasm_cmd(wr_fd, rd_fd);
    //write(wr_fd, "\n", 1);
    return (0);
}