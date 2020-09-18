// #include "asm_op.h"
#include "asm.h"
// #include "libft/libft.h"

int		is_label(char *line, t_champ *champ)
{
	int i;
	int len;
	t_l *new;

	i = 0;
	////printf("HEY\n");
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	len = i;
	while (line[i] != ' ' && line[i] != '\t' && line[i] != LABEL_CHAR &&\
	line[i] != '\0' && line[i] != COMMENT_CHAR && char_in_label(line[i]))
		i++;
	if (line[i] == LABEL_CHAR)
	{
		champ->labels[champ->l_size].is_label = 1;
		if (champ->labels[champ->l_size].names == NULL)
		{
			////printf("hey\n");
			new = malloc(sizeof(t_l));
			ft_strncpy(new->name, &line[len], i - len);
			new->name[i - len] = '\0';
			// //printf("%s - name\n", new->name);
			////printf("hey\n");
			new->next = NULL;
			champ->labels[champ->l_size].names = new;
			////printf("%s - LABEL\n", champ->labels[champ->l_size].names->name);
			champ->labels[champ->l_size].start = new;
		}
		else
		{
			new = malloc(sizeof(t_l));
			ft_strncpy(new->name, &line[len], i - len);
			new->name[i - len] = '\0';
			new->next = NULL;
			champ->labels[champ->l_size].names->next = new;
			champ->labels[champ->l_size].names = new;
		}
		
	}
	else
	{
		return (0);
	}
	i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	// //printf("%c _!_!_\n", line[i]);
	if (line[i] == '\0'|| line[i] == COMMENT_CHAR)
		return (1);
	else if (is_command(&line[i], champ))
	{
		return (1);
	}
	else
	{
		//error
		free_all(*champ);
		//printf("если это не команда\n");
		exit(-1);
	}
}
