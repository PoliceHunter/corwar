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

//Эта операция записывает значение из регистра, который был передан как первый
// параметр. А вот куда данная операция его записывает, зависит от типа второго аргумента
//Циклы до исполнения 5
//1) получаем значение из регистра, обозначенного первым аргументом
//2) смотрим тип второго аргумента и его значение
//изменения в структуре каретки
//Если второй аргумент соответствует типу T_REG, то значение (1) записывается в регистр (2)
//Если второй аргумент соответствует типу T_IND, находим
// адрес памяти = текущая позиция + <ВТОРОЙ_АРГУМЕНТ> % IDX_MOD (по модулю)

void				st(t_cor *cor, t_process *proc)
{
	int32_t			reg1num;
	int32_t			reg2num;
	int32_t			regvalue;
	int32_t			address;
	int32_t			arg2;

	reg1num = cor->map[get_address(proc, 2, 0)];
	regvalue = proc->reg[reg1num - 1];
	if (cor->buffer_codes[1] == REG_CODE)
	{
		reg2num = cor->map[get_address(proc, get_step(cor, proc, 1), 0)];
		proc->reg[reg2num - 1] = regvalue;
	}
	if (cor->buffer_codes[1] == IND_CODE)
	{
		arg2 = byte_to_int32(cor, proc, 1, cor->buffer_sizes[1]);
		//arg2 = get_value(cor, proc, 1);
		address = get_address(proc, arg2 % IDX_MOD, 0);
//		address = proc->pos + arg2 % IDX_MOD;
//		if (address < 0)
//			???;
		value32_to_map(cor, regvalue, address, DIR_SIZE);
	}
	//print_arena(cor->map, 64);
}
