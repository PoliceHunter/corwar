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

//загрузка значения из команды в регистр каретки (3 арг)
// Значением, которая эта операция записывает, являются считанные 4 байта.
//Они считываются по адресу, который формируется по следующему принципу:
// текущая позиция + (<ЗНАЧЕНИЕ_ПЕРВОГО_АРГУМЕНТА> + <ЗНАЧЕНИЕ_ВТОРОГО_АРГУМЕНТА>).
//В отличие от операции ldi в этом случае при формировании адреса не нужно делать усечение по модулю IDX_MOD.
// Размер T_DIR 2.
//Циклы до исполнения 50

void				lldi(t_cor *cor, t_process *proc)
{
	int32_t			value_to_reg; //результат побитового "и", которое нужно записать в регистр (3 арг)
	int32_t			value1;
	int32_t			value2;
	uint8_t			reg3;
	int32_t			address;

	reg3 = cor->map[get_address(proc, get_step(cor, proc, 2), 0)];
	value1 = get_value(cor, proc, 0);
	if (value1 == MEM_SIZE + 1)
		return;
	value2 = get_value(cor, proc, 1);
	address = proc->pos + (value1 + value2) % IDX_MOD;
	if (address < 0)
		return;
	value_to_reg = byte_to_int32_2(cor, address, 4);
	proc->reg[reg3] = value_to_reg;
}
