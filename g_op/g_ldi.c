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

//загрузка значения из команды в регистр каретки (3 арг)
// Размер T_DIR 2.
//Циклы до исполнения 25

void				ldi(t_cor *vm)
{
	//переменные
	//вычисленный адрес
	//значение из вычисленного адреса (4)

	//движение дальше
	//шаг курсора - прибавляем стандартный

	//получение данных
	//адрес: текущая позиция + (<(1)ЗНАЧЕНИЕ_ПЕРВОГО_АРГУМЕНТА> + <(2)ЗНАЧЕНИЕ_ВТОРОГО_АРГУМЕНТА>) % IDX_MOD
	// число из этого адреса 4 байт (4)
	// Значение: если T_REG,
	// то берем из указанного регистра
	// T_DIR
	//В данном случае у нас аргумент уже содержит свое значение
	// T_IND
	//Чтобы получить значение этого аргумента, нужно считать 4 байта по адресу — текущая позиция + <ПЕРВЫЙ_АРГУМЕНТ> % IDX_MOD.

	//изменения в структуре каретки
	//загружаем число из адреса (4) в регистр каретки (3)

	//печать
	// ft_printf("P %4d | ldi %d %d r%d\n", cursor->id, addr_1, addr_2, reg_id);
	//	ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
	//									addr_1,
	//									addr_2,
	//									addr_1 + addr_2,
	//									cursor->pc + (addr_1 + addr_2) % IDX_MOD);
}