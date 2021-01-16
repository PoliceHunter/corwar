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


int32_t			get_begin_point(t_cor *cor, t_process *proc, int i)
{
	int 		i1;
	int32_t		begin;

	i1 = 0;
	begin = 0;
	while (i1 < i)
	{
		begin = begin + cor->buffer_sizes[i1];
		i1++;
	}
	return (begin + 2);
}


int32_t		get_value(t_cor *cor, t_process *proc, int i)
{
	int32_t	res;
	int addr;

	addr = cor->map[proc->pos + get_begin_point(cor, proc, i)];
	if (cor->buffer_codes[i] == REG_CODE)
	{

		int get_nomer_registra = addr;
		int32_t get_reg_value = proc->reg[get_nomer_registra];
		res = get_reg_value;
	}
	if (cor->buffer_codes[i] == IND_CODE)
	{
		int32_t get_ind_value = bytecode_to_int32(addr, cor->buffer_sizes[i]);
		res = get_ind_value;
	}
}

int32_t		byte_to_int32(t_cor *cor, t_process *process, int i1, int size)
{
	int32_t	res;
	int 	znak;
	int		i;

	//int mesto;
	//int val;
	//int sd;
	//int i2 = 0;

	res = 0;
	znak = 0;
	if ((cor->map[process->pos + get_begin_point(cor, process, i1)] & 0x80) >> 7 == 1)
		znak = 1;
	i = 0;
	while (size)
	{
		if (znak == 1)
			res = res + ((cor->map[process->pos + get_begin_point(cor, process, i1)] ^ 0xFF) << (i++ * 8));
		else
		{
			//mesto = process->pos + get_begin_point(cor, process, i1) + size - 1;
			//val = cor->map[mesto];
			//sd = val << (i2++ * 8);
			res = res + (cor->map[process->pos + get_begin_point(cor, process, i1) + size - 1] << (i++ * 8));
		}
		size--;
	}
	if (znak == 1)
		res = ~(res);
	return (res);
}

void			value32_to_map(t_cor *cor, int32_t value, uint32_t address, int size)
{
	int8_t		i;
	uint32_t	finaddr;

	i = 0;
	while (size)
	{
		finaddr = address + size - 1;
		if (finaddr > MEM_SIZE)
			finaddr = finaddr - MEM_SIZE;
		cor->map[finaddr] = (uint8_t)((value >> i) & 0xFF);
		i += 8;
		size--;
	}
}