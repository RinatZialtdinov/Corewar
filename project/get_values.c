// #include "asm_op.h"
#include "asm.h"
// #include "libft/libft.h"

int	get_reg_arg_val(t_champ *champ, char *line, int *i)
{
	// int i;

	// i = 1;
	(*i)++;
	while (line[*i] >= '0' && line[*i] <= '9')
		(*i)++;
	if (ft_atoi(&line[1]) > REG_NUMBER || *i == 1 || ft_atoi(&line[1]) < 1)
	{
		// error Невалидный аргумент
		free_all(*champ);
		exit(0);
	}
	return (ft_atoi(&line[1]));
}

int	get_dir_ind_arg_val(t_champ *champ, char *line, int *i)
{
	int start;

	start = *i;
	if (line[*i] == '-')
		(*i)++;
	while (line[*i] >= '0' && line[*i] <= '9')
		(*i)++;
	if (line[*i - 1] == '-' && *i == 1)
	{
		// error Невалидный аргумент2
		printf("Невалидный аргумент2\n");
		free_all(*champ);
		exit(0);
	}
	return (ft_atoi(&line[start]));
}