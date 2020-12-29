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

//записывает значение, полученное из первого аргумента, в регистр, переданный
// как второй аргумент. Но если T_IND, то в этой операции мы будем считывать 4 байта
// значения по адресу — текущая позиция + <ПЕРВЫЙ_АРГУМЕНТ>. Не применяя усечение по модулю
// Оригинальная виртуальная машина corewar, к сожалению, работает неправильно. И считывает 2 байта, а не 4.
//Циклы до исполнения 10

void				lld(t_cor *vm)
{
	//переменные
	// число из первого аргумента, если 1 рег - T_DIR, или число из адреса, если 2 рег - T_IND
	//номер регистра каретки, который передается как 2 аргумент
	//вычисленный адрес, если 2 рег - T_IND

	//движение дальше
	//шаг курсора - прибавляем стандартный

	//получение данных
	//аргументы из операции
	//число из поля по адресу

	//изменения в структуре каретки
	//1- если аргумент T_DIR, загружаем значение из 2 аргумента в регистр. Если значение == 0, carry  = 1, в ост
	//случаях carry = 0
	//2- если аргумент T_IND,
	// 1) адрес = текущая позиция + <ПЕРВЫЙ_АРГУМЕНТ>
	// 2) считываем 4 байта с адреса
	// 3) записываем считанное число в регистр (переданный как 2 арг)

	//печать
	// ft_printf("P %4d | lld %d r%d\n", cursor_id, value, r_id);
}