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

#include "corwar.h"
#include "g_corewar_op.h"

int				check_arg_reg(t_cor *cor, t_process *process, int i)
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
}

int				read_args_types(t_cor *cor, t_process *process)
{
	uint8_t		type_code;
	int 		i;
	int 		check;

	check = 1;
	i = 0;
	SIZES[1] = process->op.dir_size;
	type_code = cor->map[get_address(process, 1, 0)];
	while (i < process->op.args_num)
	{
		if (process->op.args_types_code == 0)
		{
			cor->buffer_codes[i] = process->op.args_codes1[i];
			cor->buffer_sizes[i] = SIZES[cor->buffer_codes[i] - 1];
			cor->next_step = cor->next_step + cor->buffer_sizes[i];
		}
		else
		{
			cor->buffer_codes[i] = (type_code & CALC[i]) >> SDVIG[i];
			if (cor->buffer_codes[0] != 0)
			{
				cor->buffer_sizes[i] = SIZES[cor->buffer_codes[i] - 1];
				cor->next_step = cor->next_step + cor->buffer_sizes[i];
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
	cor->next_step = 0;
	//process->op_code = cor->map[process->pos];
	//ft_printf("check cor->map[process->pos]: %d\n", cor->map[process->pos]);
	if (process->op_code > 0 && process->op_code < 17)
	{
		cor->next_step = 1 + process->op.args_types_code;
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
	cor->next_step = 0;
	process->op_code = cor->map[process->pos];
	//ft_printf("read_op process->op_code: %d\n", process->op_code);
	if (process->op_code > 0 && process->op_code < 17)
	{
		process->op = g_op[process->op_code - 1];
		process->cycle_to_exec = process->op.cycles;
		return (1);
	}
	else
		return (0);
}

void			game_in_cycle(t_cor *cor)
{
	int 		index;
	int 		mem;
	t_process	*process;
	int 		check;

	index = 0;
	mem = cor->count_cursors;
	while (index < mem)
	{
		process = get_from_vec(&cor->process, index);
		//ft_printf("!!!--->>>process->player_id: %d\n", process->player_id);
		//ft_printf("process->reg[1]: %d\n", process->reg[1]);
		//ft_printf("process->pos: %d\n", process->pos);
		if (process->cycle_to_exec == -1)
		{
			check = read_op(cor, process);
			//ft_printf("-1 proc: %d pos: %d check: %d\n", process->player_id, process->pos, check);
			if (check == 1)
			{
				char *name = process->op.name;
				//ft_printf("-1 to do process->op.name: \"%s\" in %d cycle\n", process->op.name, process->cycle_to_exec);
				process->cycle_to_exec--;
				//ft_printf("cxbxf");																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																												\n", check);
			}
		}
		else if (process->cycle_to_exec == 0)
		{
			check = check_correct_op(cor, process);
			//ft_printf("check: %d\n", check);
			if (check == 1) // все проверки успешны
			{
				//ft_printf("process %d, pos: %d, done \"%s\"\n", process->player_id, process->pos, process->op.name);
				process->op.func(cor, process); //выполняем операцию
				if (process->op_code != 9)
				{
					process->op_code = 0;
					process->pos = get_address(process, cor->next_step, 1); //перепрыгиваем операцию
				}
				//ft_printf("next_pos: %d\n", process->pos);
			}
			else if (check == 2) //код операции не ок
				process->pos = get_address(process, 1, 1); //переход на след позицию
			else if (check == 3) //код операции ок, но арг или рег не ок
			{
				process->pos = get_address(process, cor->next_step, 1); //перепрыгиваем операцию
				//ft_printf("3--- process: %d, op: %d, pos: %d\n", process->player_id, process->op_code, process->pos);
			}
			//ft_printf("process->pos: %d\n", process->pos);
		}
		else
		{
			process->cycle_to_exec--;
			//ft_printf("else process->op_code: %d\n", process->op_code);
			//ft_printf("else process->cycle_to_exec: %d\n", process->cycle_to_exec);
			//ft_printf("else process->pos: %d\n", process->pos);
		}
		index++;
	}
}