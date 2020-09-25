/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 16:09:06 by damerica          #+#    #+#             */
/*   Updated: 2020/09/24 14:26:21 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM2_H
# define ASM2_H

# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4 * 1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define ALT_COMMENT			';'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

typedef char					t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		128
# define COMMENT_LENGTH			2048
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct					s_l
{
	char						name[256];
	struct s_l					*next;
}								t_l;

typedef struct					s_label
{
	int							is_label;
	t_l							*names;
	t_l							*start;
	int							range_1;
	int							range_2;
	int							range_3;
	char						cmd_name[6];
	int							cmd_code;
	int							cmd_type;
	int							arg_1;
	int							arg_2;
	int							arg_3;
	char						l_name_1[256];
	char						l_name_2[256];
	char						l_name_3[256];
	int							type_1;
	int							type_2;
	int							type_3;
	int							arg_now;
}								t_label;

typedef struct					s_champ
{
	char						name[PROG_NAME_LENGTH + 1];
	char						comment[COMMENT_LENGTH + 1];
	int							code_size;
	unsigned char				*exec_code;
	int							ind_wr;
	int							is_end_comment;

	int							new_com;
	int							l_size;
	t_label						*labels;

	int							len;
	int							fd;
}								t_champ;

typedef struct					s_tw
{
	int							comma;
	int							count_arg;
}								t_tw;

void							if_is_label(t_champ *champ, int count_arg,\
char *line, int *i);
void							recording_label(t_champ *champ, int *i,\
int count_arg, char *line);
int								skip_everything(char *line);
void							free_all(t_champ champ, char *str);
int								switch_args(char *line, int count_arg,\
t_champ *champ);
void							increase_array(t_champ *champ);
char							*check_name_com(char *line,\
t_champ *champ);
int								is_command(char *line, t_champ *champ);
void							skip_spaces(int i, char *line, t_champ *champ);
int								is_comment(char *line);
int								is_name(char **line, int fd,\
t_champ *champ, int name);
int								is_main_comment(char **line, int fd,\
t_champ *champ, int mc);
int								is_command_or_not(char *line,\
t_champ *champ);
int								find_lab_aft_cmd(t_champ *champ,\
char *l_name, int start,\
int arg);
int								is_comment(char *line);
int								is_label(char *line, t_champ *champ);
void							write_4_byte(t_champ *champ,\
unsigned int to_write);
void							write_2_byte(t_champ *champ,\
unsigned int to_write);
void							write_1_byte(t_champ *champ,\
unsigned int to_write);
void							zero_exec(t_champ *champ, int exec_size);
void							init_array(t_champ *champ);
int								get_reg_arg_val(t_champ *champ,\
char *line, int *i);
int								char_in_label(char el);
int								get_dir_ind_arg_val(t_champ *champ,\
char *line, int *i);
void							find_label(t_champ *champ);
void							is_file_valid(char *name, t_champ *champ);
void							check_type_arg(t_champ *champ);
char							*change_extension(char *filename,\
char *old, char *new);
void							to_bin_code(t_champ *champ, int fd);
void							finish_fill_label_range(t_champ *champ);
unsigned char					count_code_type_arg(t_champ *champ, int i);
int								count_code_size(t_champ *champ);

#endif
