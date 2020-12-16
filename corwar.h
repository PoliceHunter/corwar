#ifndef CORWAR_CORWAR_H
# define CORWAR_CORWAR_H

# include "libft/inc/libft.h"
# include "libft/inc/ft_printf.h"
# include "libft/inc/get_next_line.h"
# include "libft/inc/vector.h"
# include "op.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>

#define TRUE 1
#define FALSE 0
#define FULL_SIZE (CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 4)


#define TOO_MANY_PLAYERS 1
#define INVALID_FLAG_N 2
#define DUPLICATE_NUM_N 3
#define INVALID_FLAG_D 4
#define FEW_AC_DUMP 5
#define FEW_AC_N 6
#define FEW_AC_V 7
#define INVALID_PARAM 8
#define FAIL_OPEN 9
#define ERR_MAGIC 10
#define ERR_NO_NULL 11
#define INVALID_CODE_SIZE 12
#define FAIL_READ 13
#define ERR_FILE 14
#define ERR_STR_INIT 15
#define ERR_CODE_INIT 16

typedef	struct s_cflag	t_cflag;
struct			s_cflag
{
	int dump;
	int visual;
};

typedef struct s_player t_player;
struct			s_player
{
	char *name;
	char *comment;
	uint8_t *code;
	int	 player_num;
	int  index_player_ac;
	int  code_size;
};

typedef	struct s_cor	t_cor;
struct			s_cor
{
	t_cflag flag;
	t_player player[MAX_PLAYERS + 1];
	char **files;
	int cycles_to_die;
	int dump;
	int count_players;
	int count_cursors;
	int visual;
};

void exterminate(t_cor *cor, int exit_code);

#endif //CORWAR_CORWAR_H
