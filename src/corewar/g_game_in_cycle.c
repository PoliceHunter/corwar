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

	//проверить, что тип аргумента соответствует операции  != 0
	bc = cor->buffer_codes[i];
	if (bc == 0 || (bc != g_op[process->real_op_code].args_codes1[i] && bc != g_op[process->real_op_code].args_codes2[i] && bc != g_op[process->real_op_code].args_codes3[i]))
		return (0);
	///if (bc == 0 || (bc != process->op.args_codes1[i] && bc != process->op.args_codes2[i] && bc != process->op.args_codes3[i]))
	///	return (0);
	//если регистр, проверить, что от 0 до 16
	if (cor->buffer_codes[i] == REG_CODE)
	{
		code = cor->map[get_address(process, get_step(cor, process, i), 0)];
		if (code < 1 || code > 16)
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
	if (bc == 0 || (bc != process->op.args_codes1[i] && bc != process->op.args_codes2[i] && bc != process->op.args_codes3[i]))
		return (0);
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
}

void			game_in_cycle(t_cor *cor)
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
			check = check_correct_op(cor, process);
			if (check == 1) // все проверки успешны
			{
				temp = process->op_code;
				if (cor->flag.visual && cor->cycle < 12300 && process->id == 32)
				{
					ft_printf("!!done op: %s", g_op[process->real_op_code].name);
					ft_printf(" !!!!cycle %d, id %d, pos: %d, cours %d\n", cor->cycle, process->id, process->pos, cor->count_cursors);
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
