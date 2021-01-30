#ifndef CORWAR_CORWAR_H
# define CORWAR_CORWAR_H

# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"
# include "../libft/inc/vector.h"
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

#define LIVE 2
typedef	struct s_cflag	t_cflag;
struct			s_cflag
{
	int dump32; // В начале 0 , если есть флаг, то
	int dump64;	// В начале 0
	int visual; // 0 or 1
	int aff;    // 0 or 1
};

typedef struct s_player t_player;
struct			s_player
{
	char		*name;
	char		*comment;
	uint8_t		*code;
	int			id;
	int			index_player_ac;
	int			code_size;
	uint32_t	position_on_map; //position code on map
};

//(gala)---
typedef struct	s_op
{
	char		*name;
	uint8_t		op_code;
	uint8_t		args_num;
	int			args_types_code;
	int			args_codes1[3];
	int			args_codes2[3];
	int			args_codes3[3];
	int			modify_carry;
	uint8_t		dir_size;
	int			cycles;
	void 		(*func)(void *, void *);
}				t_op;
//---

typedef struct			s_process
{
	int32_t 			reg[REG_NUMBER + 1]; 	////Array of variables for storing data
	uint8_t 			carry;					//A special variable that affects the operation of the "zjmp" function and can
												// ** take one of two values: 1 or 0. If it's 1, then the function updates the ** "position
	uint32_t 			pos; 					////Map address
	uint8_t 			op_code; 				//Contains the operation code, at the time of moving to this position on the map
	uint8_t				name_op;
	//uint32_t			next_pos;
	int					cycle_to_exec; 			// A counter containing the number of cycles that the carriage must wait before starting an operation.
	int32_t				live_last_cycle; 		// Contain the cycle on which the last live operation was performed //gala убрала u
	uint32_t			live_last_id;
	uint32_t			id; 					//// index of process
	uint32_t			player_id;
	uint8_t 			real_op_code;
	//t_op				op;						// (gala) функция операции
}						t_process;

typedef	struct s_cor	t_cor;
struct					s_cor
{
	t_cflag				flag;						 ////Struct wich contain flags
	t_player			player[MAX_PLAYERS + 1]; 		////struct witch contain info about player
	t_vector			process;						////vector process
	char				**files; 							//// Our argv
	uint32_t			cycle; 						//// Cunter containing total cycles have passed since the start of the game
	int32_t				cycles_to_die; 					// The number of cycles between checks
	int32_t             cycles_after_check;             //// New param, count cycles [0;cycles_to_die]
	int					count_players; 						//// How many players in the game
	int					count_cursors; 						//// count cursors on the start = count players
	int					count_lives; 						//// (gala) считаем кол-во операций live за цикл
	int					count_check; 						// (gala) считаем кол-во проверок до MAX_CHECKS
	uint8_t				map[MEM_SIZE]; 					// our map (stored battlefield)
	int					last_live_player; 				//// The player who was last told that he was alive
	int 				*buffer_codes;			// (gala) коды операций
	int 				*buffer_sizes;			// (gala) коды операций
	int 				buffer_counter;			// (gala) счетчик кодов операций
	int 				check_arg_reg;			// (gala) 1 правильно, 0 - нет
	int 				next_step;			// (gala) временная переменная - на сколько шагов двигаться
	uint32_t 			*buf_proc_id; ////alter
	int32_t 			*reg[REG_NUMBER + 1]; 	////Array of variables for storing data
	uint8_t 			*carry;					//A special variable that affects the operation of the "zjmp" function and can
	uint32_t 			*pos; 					////Map address
	int 				valid_fork;
	uint8_t 			*op_code; 				//Contains the operation code, at the time of moving to this position on the map
	int					*cycle_to_exec; 			// A counter containing the number of cycles that the carriage must wait before starting an operation.
	int32_t				*live_last_cycle; 		// Contain the cycle on which the last live operation was performed //gala убрала u
	uint32_t			*live_last_id;
	uint32_t			*id; 					//// index of process
	uint32_t			*player_id;
	t_op				*op;					// (gala) функция операции
	uint8_t				*real_ops;
	int					alt_buf_cntr;
};

void			exterminate(t_cor *cor, int exit_code);
int32_t			bytecode_to_int32(const uint8_t *bytecode, size_t size);  //(gala) убрала статик

uint32_t		find_cycle_to_exec(t_cor *cor, t_process *proc);
void			print_arena(uint8_t *map, int print_mode);
t_process 		*init_process(int32_t pos, t_vector process, int player_id);
void 			dublicate_process(t_process *dubl, t_process *proc);

//(gala)
int32_t			byte_to_int32(t_cor *cor, t_process *process, int i, int size);
void			value32_to_map(t_cor *cor, int32_t value, uint32_t address, int size);
int 			game_logic(t_cor *cor);
void			add(t_cor *vm, t_process *proc);
void			sti(t_cor *vm, t_process *proc);
void			live(t_cor *vm, t_process *proc);
void			aff(t_cor *vm, t_process *proc);
void			and(t_cor *vm, t_process *proc);
void			g_fork(t_cor *vm, t_process *proc);
void			ld(t_cor *vm, t_process *proc);
void			ldi(t_cor *vm, t_process *proc);
void			lfork(t_cor *vm, t_process *proc);
void			lld(t_cor *vm, t_process *proc);
void			lldi(t_cor *vm, t_process *proc);
void			or(t_cor *vm, t_process *proc);
void			st(t_cor *vm, t_process *proc);
void			sub(t_cor *vm, t_process *proc);
void			xor(t_cor *vm, t_process *proc);
void			zjmp(t_cor *vm, t_process *proc);
void			game_in_cycle(t_cor *cor);
void			make_buffer_codes(t_cor *cor);
void			fill_buffer_with_zeros(t_cor *cor);
int32_t			get_begin_point(t_cor *cor, t_process *proc, int i);//
int32_t			get_address(t_process *process, int32_t step, int key);
int32_t			get_address_map(int32_t address, int32_t step);
int32_t			get_step(t_cor *cor, t_process *proc, int i);
int32_t			byte_to_int32_2(t_cor *cor, uint32_t address, int size);
int32_t			get_value(t_cor *cor, t_process *proc, int i);
int 			check_flag(t_cor *cor);
void 			proverka(t_cor *cor);
void    		init_cor(t_cor *cor, char **av);
void    		init_arena(t_cor *cor);
t_process		*init_process(int32_t pos, t_vector process, int player_id);
void 			init_processes(t_cor *cor);
void			print_arena(uint8_t *map, int print_mode);
void			print_intro(t_cor *cor);
void 			parse_dump_flag(t_cor *cor, char *num, int *i, int ac);
void 			parse_d_flag(t_cor *cor, char *num, int *i, int ac);
void			parse_flags(t_cor *cor, int ac, char **av);
int				is_filename(const char *filename, const char *ext);
void 			parse_champion_file(t_cor *cor);
void			save_empty_num_player(t_cor *cor, const int *i);
void			save_num_player(t_cor *cor, char *num, int *i, int ac);
void			error_usage(void);

#endif //CORWAR_CORWAR_H
