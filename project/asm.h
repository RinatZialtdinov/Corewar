/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 16:09:06 by damerica          #+#    #+#             */
/*   Updated: 2020/09/01 16:09:09 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ASM_H
# define ASM_H

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

/*
**
*/

typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					3
#define T_LAB					8

/*
**
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct s_l
{
	char		name[256];
	struct s_l	*next;
}				t_l;

typedef struct  s_label
{
	int		is_label;
	t_l		*names;
	t_l		*start; // название метки если это она
	int		range_1; /*Расстояние до метки или значение аргумента*/
	int		range_2;
	int		range_3;
	char	cmd_name[6]; // название команды
	int		cmd_code; // код команды в 16 системе
	int		cmd_type; // 1 если больше одного арг. или 0
	int		arg_1; /*Размер аргумента в кол-ве байт*/
	int		arg_2;
	int		arg_3;
	char	l_name_1[256]; /*Названия метки если какой-либо аргумент является меткой */
	char	l_name_2[256];
	char	l_name_3[256];
	int		type_1; // тип аргумента (1 - T_REG, 2 - T_DIR, 3 - T_IND)
	int		type_2;
	int		type_3;
	int 	arg_now; 		
}               t_label;

typedef struct  s_champ
{
	char    name[PROG_NAME_LENGTH + 1];
	char    comment[COMMENT_LENGTH + 1];
	int     code_size;
	unsigned char    *exec_code;
	int		ind_wr;

	int		new_com;
	int		l_size;
	t_label	*labels;
}               t_champ;


#endif