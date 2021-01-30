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


int32_t			get_step(t_cor *cor, t_process *proc, int i)
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
	begin = begin + 1 + g_op[proc->real_op_code].args_types_code;
	return (begin);
}


int32_t			get_value(t_cor *cor, t_process *proc, int i)
{
	int32_t		res;
	int			num;
	int32_t	addr;

	res = 0;
	num = 0;
	if (cor->buffer_codes[i] == REG_CODE)
	{
		num = byte_to_int32(cor, proc, i, cor->buffer_sizes[i]);
		res = proc->reg[num];
	}
	else if (cor->buffer_codes[i] == DIR_CODE)
	{
		res = byte_to_int32(cor, proc, i, cor->buffer_sizes[i]);
	}
	else if (cor->buffer_codes[i] == IND_CODE)
	{
		num = byte_to_int32(cor, proc, i, cor->buffer_sizes[i]); //2 т.к. ИНД
		if (num < 0)
			return (MEM_SIZE + 1);///
		if (g_op[proc->real_op_code].op_code != 13 && g_op[proc->real_op_code].op_code != 14)
			addr = get_address(proc, num % IDX_MOD, 0);
		else
			addr = get_address(proc, num, 0);
		res = byte_to_int32_2(cor, addr, 4);
	}
	return (res);
}

int32_t		byte_to_int32(t_cor *cor, t_process *process, int i1, int size) //а что если число частично перенесено?
{
	int32_t	res;
	int 	znak;
	int		i;

	int mesto;
	int val;
	int sd;
	int i2 = 0;

	res = 0;
	znak = 0;

	int gs;
	int ga;
	int val1;
	int sd1;

	gs = get_step(cor, process, i1);
	ga = get_address(process, gs, 0);
	val1 = cor->map[ga];
	sd1 = val1 & 0x80;
	sd1 = sd1 >> 7;


	if ((cor->map[get_address(process, get_step(cor, process, i1), 0)] & 0x80) >> 7 == 1)
		znak = 1;
	i = 0;
	while (size)
	{
		if (znak == 1)
			res = res + ((cor->map[get_address(process, get_step(cor, process, i1) + size - 1, 0)] ^ 0xFF) << (i++ * 8));
		else
		{
			mesto = process->pos + get_step(cor, process, i1) + size - 1;
			val = cor->map[mesto];
			sd = val << (i2++ * 8);
			res = res + (cor->map[get_address(process, get_step(cor, process, i1) + size - 1, 0)] << (i++ * 8));
		}
		size--;
	}
	if (znak == 1)
		res = ~(res);
	return (res);
}

int32_t		byte_to_int32_2(t_cor *cor, uint32_t address, int size) //а что если число частично перенесено?
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
	if ((cor->map[address] & 0x80) >> 7 == 1)
		znak = 1;
	i = 0;
	while (size)
	{
		if (znak == 1)
			res = res + ((cor->map[get_address_map(address, size - 1)] ^ 0xFF) << (i++ * 8));
		else
		{
			//mesto = process->pos + get_begin_point(cor, process, i1) + size - 1;
			//val = cor->map[mesto];
			//sd = val << (i2++ * 8);
			res = res + (cor->map[get_address_map(address, size - 1)] << (i++ * 8));
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
	uint32_t	finaddr;///

	i = 0;
	while (size)
	{
		finaddr = address + size - 1;
		if (finaddr > MEM_SIZE)
			finaddr = finaddr % MEM_SIZE;
		cor->map[finaddr] = (uint8_t)((value >> i) & 0xFF);
		i += 8;
		size--;
	}
}

int32_t		get_address(t_process *process, int32_t step, int key)
{
	int32_t	address;

	address = process->pos + step;
	if (address > MEM_SIZE)
		address = address % MEM_SIZE;
	if (key == 1)
		process->cycle_to_exec = -1;
	return (address);
}

int32_t		get_address_map(int32_t address, int32_t step)
{
	int32_t	address2;

	address2 = address + step;
	if (address2 > MEM_SIZE)
		address2 = address2 % MEM_SIZE;
	return (address2);
}