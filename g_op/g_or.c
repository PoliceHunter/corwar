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

//«побитовое ИЛИ» для значений первых двух аргументов и
// записывает полученный результат в регистр, переданный в качестве третьего аргумента
//Циклы до исполнения 6

void				or(t_cor *vm)
{
	//переменные
	//value = результат побитового "или", которое нужно записать в регистр (3 арг)
	//value_1
	//value_2

	//движение дальше
	//шаг курсора - прибавляем стандартный

	//получение данных
	//--Если тип 1 и 2 аргумента T_REG
	//В данном случае значение берется из регистра, переданного в качестве аргумента
	//--Если тип 1 и 2 аргумента T_DIR
	//В этом случае используется переданное в качестве аргумента числовое значение.
	//--Если тип 1 и 2 аргумента T_IND
	//необходимо установить адрес, с которого будет считано 4 байта
	// текущая позиция + <АРГУМЕНТ> % IDX_MOD.
	// Считанное по этому адресу 4-байтовое число и будет требуемым значением
	// 2 числа побитово "или": value = value_1 | value_2;

	//изменения в структуре каретки
	//побитовая операция and для (1) и (2), загружаем это значение в регистр каретки (3). Если значение == 0, то carry  = 1, в ост
	//случаях carry = 0

	//печать ft_printf("P %4d | or %d %d r%d\n", cursor_id, value_1, value_2, r_id);
}