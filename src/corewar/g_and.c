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


//«побитовое И» для значений первых двух аргументов и
// записывает полученный результат в регистр, переданный в качестве третьего аргумента
//Циклы до исполнения 6

void				and(t_cor *cor, t_process *proc)
{
	int32_t			value_to_reg; //результат побитового "и", которое нужно записать в регистр (3 арг)
	int32_t			value1;
	int32_t			value2;
	uint8_t			reg3;

	reg3 = cor->map[get_address(proc, get_step(cor, proc, 2), 0)];
	value1 = get_value(cor, proc, 0);
	if (value1 == MEM_SIZE + 1)
		return;
	value2 = get_value(cor, proc, 1);
	value_to_reg = value1 & value2;
	proc->reg[reg3 - 1] = value_to_reg;
	if (value_to_reg == 0)
		proc->carry = 1;
	else
		proc->carry = 0;
}

