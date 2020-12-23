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
	int dump32;
	int dump64;
	int visual;
};

typedef struct s_player t_player;
struct			s_player
{
	char *name;
	char *comment;
	uint8_t *code;
	int	 id;
	int  index_player_ac;
	int  code_size;
};


typedef struct			s_process
{
	int32_t 			reg[REG_NUMBER + 1]; 	//Array of variables for storing data
	uint8_t 			carry; 					// Can be 1 or 0. If it's 1, then the func updates the "position"
	uint32_t 			pos; 					//Map address
	uint8_t 			op_code; 				//Contain op code
	//uint32_t			next_pos;
	uint32_t			cycle_to_exec; 			// A counter containing the number of cycles that the carriage must wait before starting an operation.
	uint32_t			live_last_cycle; 		// Contain the cycle on which the last live operation was performed
	uint32_t			live_last_id;
	uint32_t			id; 					// index of process
	uint32_t			player_id;
}						t_process;

typedef	struct s_cor	t_cor;
struct			s_cor
{
	t_cflag flag;						 //Struct wich contain flags
	t_player player[MAX_PLAYERS + 1]; 		//struct witch contain info about player
	t_vector process;						//vector process
	char **files; 							// Our argv
	uint32_t cycle; 						// Cunter containing total cycles have passed since the start of the game
	int32_t  cycle_to_check; 				// Counter containing the number of cycles left before the check
	int32_t cycles_to_die; 					// The number of cycles between checks
	int count_players; 						// How many players in the game
	int count_cursors; 						// count cursors on the start = count players
	uint8_t map[MEM_SIZE]; 					// our map (stored battlefield)
	int last_live_player; 					// The player who was last told that he was alive

};

void exterminate(t_cor *cor, int exit_code);

#endif //CORWAR_CORWAR_H
