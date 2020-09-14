#include "asm.h"

void is_header_valid(int fd, t_champ *champ)
{
	int name;
	int mc;
	char *line;
	int ans;

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
		{
			//error
			printf("hey\n");
			printf("%s\n", line);
			free_all(*champ);
			exit(0);
		}
		free(line);
	}
}

void	is_body_valid(int fd, t_champ *champ)
{
	int ans;
	char *line;

	while ((ans = get_next_line(fd, &line)) > 0)
	{
		//printf("%s\n", line);
		if (is_comment(line))
			;
		else if (is_command(line, champ))
			;
		else if (is_label(line, champ))
			;
		else
		{
			// ERROR nevalidnyi vvod
			free_all(*champ);
			printf("nevalidnyi vvod\n");
			exit(0);
		}
		free(line);
	}
	finish_fill_label_range(champ);
}

void	is_file_valid(char *name, t_champ *champ)
{
	int len;
	int fd;

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
	{
		//error неправильное название файла
		//printf("неправильное название файла\n");
		exit (0);
	}
	close(fd);
	fd = open(name, O_RDONLY);
	int is_ok_to_end = 0;
	char buff[2000000];
	int length = read(fd, &buff, 2000000);
	if (!(buff[length] == '\0' && buff[length-1] == '\n'))
	{
		//error
		exit(0);
	}
}
