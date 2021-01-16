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

//Эта операция записывает значение из регистра, который был передан как первый
// параметр. А вот куда данная операция его записывает, зависит от типа второго аргумента
//Циклы до исполнения 5


void				st(t_cor *vm, t_process *proc)
{
	//переменные
	//значение, которое надо записать (1)

	//движение дальше
	// шаг курсора - прибавляем стандартный

	//получение данных
	//1) получаем значение из регистра, обозначенного первым аргументом
	//2) смотрим тип второго аргумента и его значение

	//изменения в структуре каретки
	//Если второй аргумент соответствует типу T_REG, то значение (1) записывается в регистр (2)
	//Если второй аргумент соответствует типу T_IND, находим
	// адрес памяти = текущая позиция + <ВТОРОЙ_АРГУМЕНТ> % IDX_MOD (по модулю)

	//изменения в общей структуре vm
	//в случае T_IND записать значение (1), в память по полученному адресу.

	//печать
	//ft_printf("P %4d | sub r%d r%d r%d\n", cursor_id, r1_id, r2_id, r3_id);
}
