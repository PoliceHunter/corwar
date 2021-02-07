/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljacquet <ljacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 11:56:21 by ljacquet          #+#    #+#             */
/*   Updated: 2020/12/18 14:48:30 by ljacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corwar.h"
#include "../../includes/g_corewar_op.h"

int				check_arg_reg(t_cor *cor, t_process *process, int i) ///alt
{
	int32_t		code;
	int 		bc;

	int step; ///

	//проверить, что тип аргумента соответствует операции  != 0
	bc = cor->buffer_codes[i];
	if (bc == 0 || (bc != g_op[process->real_op_code].args_codes1[i] && bc != g_op[process->real_op_code].args_codes2[i] && bc != g_op[process->real_op_code].args_codes3[i]))
		return (0);
	///if (bc == 0 || (bc != process->op.args_codes1[i] && bc != process->op.args_codes2[i] && bc != process->op.args_codes3[i]))
	///	return (0);
	//если регистр, проверить, что от 0 до 16
	if (cor->buffer_codes[i] == REG_CODE)
	{
		step = get_step(cor, process, i);
		code = cor->map[85];
		code = cor->map[86];
		code = cor->map[87];
		code = cor->map[get_address(process, get_step(cor, process, i), 0)];
		if (code < 1 || code > 16) ///regs 16
			return (0);
	}
	return (1);
}

/*int				check_arg_reg(t_cor *cor, t_process *process, int i)
{
	int32_t		code;
	int 		bc;

	//проверить, что тип аргумента соответствует операции  != 0
	bc = cor->buffer_codes[i];
	//if (bc == 0 || (bc != process->op.args_codes1[i] && bc != process->op.args_codes2[i] && bc != process->op.args_codes3[i]))
	//	return (0);
	//если регистр, проверить, что от 0 до 16
	if (cor->buffer_codes[i] == REG_CODE)
	{
		code = cor->map[get_address(process, get_step(cor, process, i), 0)];
		if (code < 1 || code > 16)
			return (0);
	}
	return (1);
}*/

int				read_args_types(t_cor *cor, t_process *process)
{
	uint8_t		type_code;
	int 		i;
	int 		check;

	check = 1;
	i = 0;
	SIZES[1] = g_op[process->real_op_code].dir_size;
	type_code = cor->map[get_address(process, 1, 0)];
	while (i < g_op[process->real_op_code].args_num)///
	{
		///if (process->op.args_types_code == 0)
		if (g_op[process->real_op_code].args_types_code == 0)///
		{
			cor->buffer_codes[i] = g_op[process->real_op_code].args_codes1[i];///
			cor->buffer_sizes[i] = SIZES[cor->buffer_codes[i] - 1];
			process->next_step = process->next_step + cor->buffer_sizes[i];
		}
		else
		{
			cor->buffer_codes[i] = (type_code & CALC[i]) >> SDVIG[i];
			if (cor->buffer_codes[0] != 0)
			{
				cor->buffer_sizes[i] = SIZES[cor->buffer_codes[i] - 1];
				process->next_step = process->next_step + cor->buffer_sizes[i];
				if (check_arg_reg(cor, process, i) == 0)
					check = 0;
			}
			else
				check = 0;
		}
		i++;
	}
	return (check);
}

int				check_correct_op(t_cor *cor, t_process *process)
{
	fill_buffer_with_zeros(cor);
	process->next_step = 0;
	//process->op_code = cor->map[process->pos];
	//ft_printf("check cor->map[process->pos]: %d\n", cor->map[process->pos]);
	if (process->op_code > 0 && process->op_code < 17)
	{
		process->next_step = 1 + g_op[process->real_op_code].args_types_code;
		//process->op = g_op[process->op_code - 1];
		if (read_args_types(cor, process) == 0)
			return (3);
		//process->cycle_to_exec = process->op.cycles;
		return (1);
	}
	else
		return (2);
}

int				read_op(t_cor *cor, t_process *process)
{
	fill_buffer_with_zeros(cor);
	process->next_step = 0;
	process->op_code = cor->map[process->pos];
	if (process->op_code > 0 && process->op_code < 17)
	{
		///process->op = g_op[process->op_code - 1];
		///process->cycle_to_exec = process->op.cycles;
		process->real_op_code = process->op_code - 1;
		process->cycle_to_exec = g_op[process->real_op_code].cycles;
		return (1);
	}
	else
		return (0);
}

void 			new_place(t_cor *cor, t_process *process)
{
	int 		check;

	check = read_op(cor, process);
	if (cor->flag.visual)// && cor->cycle > 1720 && cor->cycle < 1750)
	{
		//ft_printf("!!to do op: \"%s\" in %d cycles", g_op[process->op_code - 1].name, process->cycle_to_exec);
		//ft_printf("  !!!!cycle %d, process %d, pos: %d\n", cor->cycle, process->player_id, process->pos);
	}
	if (check == 1)
		process->cycle_to_exec--;
	else
		process->cycle_to_exec = 0;
}

void			game_in_cycle1(t_cor *cor)
{
	int 		index;
	t_process	*process;
	int 		check;
	int 		temp;
	int 		prev_curs;

	//temp = -1;
	index = -1;
	prev_curs = cor->count_cursors;
	while (++index < cor->count_cursors)
	{
		process = get_from_vec(&cor->process, index);
		//if (process->carry == 1)
			//ft_printf("\nCarry");
		if (cor->flag.visual && cor->cycle == 0)
			ft_printf("\nContestant №%d pos: %d\n", process->player_id, process->pos);

		if (process->cycle_to_exec == 0)
		{
			if (cor->flag.visual && cor->cycle < 600)// && process->id == 32)
			{
				//ft_printf("!op: %d", g_op[process->real_op_code].op_code);
				//ft_printf(" cy %d, id %d, pos: %d, car %d, crs %d, liv %d", cor->cycle, process->id, process->pos, process->carry, cor->count_cursors, cor->count_lives);
				//ft_printf(" //r %d=%d=%d=%d\n", process->reg[0], process->reg[1], process->reg[2], process->reg[14]);
				//ft_printf("cy=%d, c=%d, m1=%d, m2=%d, m3=%d, m4=%d\n", cor->cycle, process->id, cor->map[2112], cor->map[2113], cor->map[2114], cor->map[2115]);
			}
			check = check_correct_op(cor, process);
			if (check == 1) // все проверки успешны
			{
				temp = process->op_code;
				if (cor->flag.visual && cor->cycle < 17100 && process->id == 8)
				{
//					ft_printf("!op: %d", g_op[process->real_op_code].op_code);
//					ft_printf(" cy %d, id %d, pos: %d, car %d, crs %d, liv %d", cor->cycle, process->id, process->pos, process->carry, cor->count_cursors, cor->count_lives);
//					ft_printf(" //r %d=%d=%d=%d\n", process->reg[0], process->reg[1], process->reg[2], process->reg[3]);
					//ft_printf("cy=%d, c=%d, =%d, =%d, =%d, =%d\n", cor->cycle, process->id, cor->map[3718], cor->map[3719], cor->map[3720], cor->map[3721]);
				}
				g_op[process->real_op_code].func(cor, process); ///выполняем операцию
				if (temp == 12 && cor->valid_fork == 1)
				{
					//process = get_from_vec(&cor->process, index + 1);
					index++;
					process = get_from_vec(&cor->process, index);
				}
				if (process->op_code != 9)
				{
					process->op_code = 0;
					process->real_op_code = 0;
					process->pos = get_address(process, process->next_step, 1); //перепрыгиваем операцию
				}
				//if (cor->flag.visual) // && cor->cycle > 1720 && cor->cycle < 1750)
					//ft_printf("  ->next_pos: %d\n", process->pos);
			}
			else if (check == 2) //код операции не ок
				process->pos = get_address(process, 1, 1); //переход на след позицию
			else if (check == 3) //код операции ок, но арг или рег не о
				process->pos = get_address(process, process->next_step, 1); //перепрыгиваем операцию
		}
		if (process->cycle_to_exec == -1)
			new_place(cor, process);
		else
			process->cycle_to_exec--;
	}
}

void	update_opcod(t_cor *cor, t_process *proc)
{
	proc->op_code = cor->map[proc->pos];
	if (cor->map[proc->pos] >= 1 && cor->map[proc->pos] <= 16)
		proc->cycle_to_exec = g_op[proc->op_code - 1].cycles;
}

void		parse_codetype(t_cor *cor, t_process *process)
{
	int8_t  type_code;
	int 	i;

	i = 0;
	fill_buffer_with_zeros(cor);
	SIZES[1] = g_op[process->real_op_code].dir_size;
	type_code = cor->map[get_address(process, 1, 0)];
	process->op_step = 1 + g_op[process->real_op_code].args_types_code;
	while (i < g_op[process->real_op_code].args_num)
	{
		if (g_op[process->real_op_code].args_types_code == 0)
		{
			cor->buffer_codes[i] = g_op[process->real_op_code].args_codes1[i];///
			cor->buffer_sizes[i] = SIZES[cor->buffer_codes[i] - 1];
			process->op_step = process->op_step + cor->buffer_sizes[i];
		}
		else
		{
			cor->buffer_codes[i] = (type_code & CALC[i]) >> SDVIG[i];
			cor->buffer_sizes[i] = SIZES[cor->buffer_codes[i] - 1];
			process->op_step = process->op_step + cor->buffer_sizes[i];
		}
		i++;
	}
}

int			arg_types_valid(t_cor *cor, t_process *process)
{
	int32_t i;
	int 		bc;

	i = 0;

	while (i < g_op[process->real_op_code].args_num)
	{
		bc = cor->buffer_codes[i];
		if (bc == 0 || (bc != g_op[process->real_op_code].args_codes1[i] && bc != g_op[process->real_op_code].args_codes2[i] && bc != g_op[process->real_op_code].args_codes3[i]))
			return (0);
		i++;
	}
	return (1);
}

int			is_register(t_cor *cor, t_process *process, int32_t step)
{
	int8_t r_id;

	r_id = cor->map[get_address(process, step, 0)];
	if (r_id >= 1 && r_id <= REG_NUMBER)
		return (1);
	else
		return (0);
}

uint32_t	step_size(uint8_t arg_type, t_process *process)
{
	if (arg_type == 1)
		return (1);
	else if (arg_type == 2)
		return (g_op[process->real_op_code].dir_size);
	else if (arg_type == 3)
		return (IND_SIZE);
	return (0);
}

int			is_args_valid(t_cor *cor, t_process *process)
{
	int32_t		i;
	uint32_t	step;

	i = 0;
	step = (1 + (g_op[process->real_op_code].args_types_code ? 1 : 0));
	while (i < g_op[process->real_op_code].args_num)
	{
		if ((cor->buffer_codes[i] == T_REG)
			&& is_register(cor, process, step) == 0)
			return (0);
		step += step_size(cor->buffer_codes[i], process);
		i++;
	}
	return (1);
}

uint32_t	calc_step(t_cor *cor, t_process *process)
{
	int32_t		i;
	uint32_t	step;

	i = 0;
	step = 0;
	step += 1 + (g_op[process->real_op_code].args_types_code ? 1 : 0);
	while (i < g_op[process->real_op_code].args_num)
	{
		step += cor->buffer_sizes[i];
		i++;
	}
	return (step);
}

void			game_in_cycle(t_cor *cor)
{
	int 		index;
	int 		temp;
	t_process	*process;

	index = -1;
	while (++index < cor->count_cursors)
	{
		process = get_from_vec(&cor->process, index);

		if (process->cycle_to_exec == 0)
			update_opcod(cor, process);
		if (process->cycle_to_exec > 0)
			process->cycle_to_exec--;
		if (process->cycle_to_exec == 0)
		{
			process->real_op_code = -1;
			if (process->op_code >= 1 && process->op_code <= 16)
				process->real_op_code = process->op_code - 1;
			if (process->op_code >= 1 && process->op_code <= 16)
			{
				parse_codetype(cor, process);
				if (arg_types_valid(cor, process) == 1 && is_args_valid(cor, process) == 1)
				{
					if (cor->flag.visual && process->id == 4)// && cor->cycle < 8150 && process->id == 4)
					{
						ft_printf("!op: %d", g_op[process->real_op_code].op_code);
						ft_printf(" cy %d, id %d, pos: %d, car %d, crs %d, liv %d", cor->cycle, process->id, process->pos, process->carry, cor->count_cursors, cor->count_lives);
						ft_printf(" //r %d=%d=%d=%d\n", process->reg[0], process->reg[1], process->reg[2], process->reg[3]);
						//ft_printf("cy=%d, c=%d, =%d, =%d, =%d, =%d\n", cor->cycle, process->id, cor->map[41], cor->map[42], cor->map[43], cor->map[44]);
					}
					temp = process->op_code;
					g_op[process->real_op_code].func(cor, process); ///выполняем операцию
					if (temp == 12 && cor->valid_fork == 1)
					{
						//process = get_from_vec(&cor->process, index + 1);
						index++;
						process = get_from_vec(&cor->process, index);
					}
					process->next_step = process->op_step;
				}
				else
					process->next_step += calc_step(cor, process);
			}
			else
				process->next_step = 1;
			process->pos = get_address(process, process->next_step, 1);
		}
	}
}