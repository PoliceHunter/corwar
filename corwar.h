#ifndef CORWAR_CORWAR_H
# define CORWAR_CORWAR_H
# include "libft/inc/libft.h"
# include "libft/inc/ft_printf.h"
# include "libft/inc/get_next_line.h"
# include "op.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
#define FULL_SIZE (CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 4)

typedef	struct s_cflag	t_cflag;
struct			s_cflag
{
	int flag1;
	int flag2;
};

typedef struct s_player t_player;
struct			s_player
{
	char name[PROG_NAME_LENGTH + 1];
	char comment[COMMENT_LENGTH + 1];
	char chmpsize[CHAMP_MAX_SIZE + 1];
	char string[FULL_SIZE + 1];
	int	 player_num;
};

typedef	struct s_cor	t_cor;
struct			s_cor
{
	t_cflag flag;
	t_player player;
	char **files;
	int cycles_to_die;
};

#endif //CORWAR_CORWAR_H
