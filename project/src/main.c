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

void	usage(void)
{
	write(1, "Usage: ./asm (champion.s|champion.cor)\n", 40);
	write(1, "    champion.s   — from assemble to bytecode\n", 47);
	write(1, "    champion.cor — from bytecode to assemble\n", 47);
}

void	main_validation(int argc, t_champ *champ, char **argv)
{
	if (argc == 1)
	{
		usage();
		exit(0);
	}
	init_array(champ);
	if (argc != 2)
		exit(0);
	else
	{
		is_file_valid(argv[1], champ);
		check_type_arg(champ);
	}
	if (champ->l_size == 0)
		exit(-1);
}

int		main(int argc, char **argv)
{
	t_champ	champ;
	int		fd;
	char	*file_name;

	main_validation(argc, &champ, argv);
	file_name = change_extension(argv[1], ".s", ".cor");
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	to_bin_code(&champ, fd);
	write(1, "Writing output program to ", 26);
	write(1, file_name, ft_strlen(file_name));
	write(1, "\n", 1);
	free(file_name);
	free(champ.exec_code);
	free_all(champ, NULL);
	return (0);
}
