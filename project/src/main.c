/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:26:09 by damerica          #+#    #+#             */
/*   Updated: 2020/09/23 12:26:10 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	usage()
{
	write(1, "Usage: ./asm (champion.s|champion.cor)\n", 39);
	write(1, "    champion.s   — from assemble to bytecode\n", 46);
	write(1, "    champion.cor — from bytecode to assemble\n", 46);
}

int		main(int argc, char **argv)
{
	t_champ	champ;
	int		fd;
	char	*file_name;

	if (argc == 1)
	{
		usage();
		return (0);
	}
	init_array(&champ);
	if (argc != 2)
		return (0);
	else
	{
		is_file_valid(argv[1], &champ);
		check_type_arg(&champ);
	}
	if (champ.l_size == 0)
		exit(-1);
	file_name = change_extension(argv[1], ".s", ".cor");
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	to_bin_code(&champ, fd);
	write(1, "Writing output program to ", 26);
	write(1, file_name, ft_strlen(file_name));
	write(1, "\n", 1);
	free_all(champ);
	free(file_name);
	free(champ.exec_code);
	return (0);
}
